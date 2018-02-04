//////////////////////////////////////////////////////////////////////////
#pragma once
#include "CPF/Std/Vector.hpp"
#include "CPF/Std/Algorithm.hpp"
#include "CPF/Std/CCType.hpp"
#include "CPF/Std/Utf8String.hpp"

//////////////////////////////////////////////////////////////////////////
namespace CPF
{
	namespace IO
	{
		namespace Path
		{
#if CPF_TARGET_WINDOWS
			static constexpr char kReversedSeparator = '\\';
			static constexpr char kOsDirectorySeparator = '\\';
			static constexpr char kDirectorySeparator = '/';
			static constexpr char kExtensionSeparator = '.';
#endif

			inline Std::Utf8String Normalize(const Std::Utf8String& path)
			{
				Std::Utf8String result;
				auto ibegin = path.begin();
				auto iend = path.end();

				while (Std::IsSpace(*ibegin))
					++ibegin;
				while (Std::IsSpace(*(iend - 1)))
					--iend;
				for (; ibegin != iend; ++ibegin)
				{
					if (*ibegin == kReversedSeparator)
						result += kDirectorySeparator;
					else
						result += *ibegin;
				}

				return result;
			}

			inline bool IsRooted(const Std::Utf8String& path)
			{
				if (path.length() >= 2 && path.at(1) == ':')
					return true;
				if (!path.empty() && path.at(0) == kDirectorySeparator)
					return true;
				return false;
			}

			inline Std::Utf8String GetRoot(const Std::Utf8String& path)
			{
				if (IsRooted(path))
				{
					if (path.length() >= 2 && path.at(1) == ':')
						return Std::Utf8String(path.begin(), path.begin() + 2);
				}
				return Std::Utf8String();
			}

			inline bool HasExtension(const Std::Utf8String& path)
			{
				auto it = Find(path.rbegin(), path.rend(), uint32_t(kExtensionSeparator));
				auto slash = Find(path.rbegin(), path.rend(), uint32_t(kDirectorySeparator));
				return it!=path.rend() && it < slash;
			}

			inline Std::Utf8String EnsureTrailingSeparator(const Std::Utf8String& path)
			{
				if (path.empty())
					return Std::Utf8String("/");
				if (path.back() == kDirectorySeparator)
					return path;
				Std::Utf8String result = path;
				result += kDirectorySeparator;
				return result;
			}

			inline Std::Utf8String Combine(const Std::Utf8String& lhs, const Std::Utf8String& rhs)
			{
				const Std::Utf8String tl = Normalize(lhs);
				const Std::Utf8String rl = Normalize(rhs);
				
				if (!tl.empty())
				{
					if (tl.back() == uint32_t(kDirectorySeparator))
						return Std::Utf8String(tl + rl);
					if (!rl.empty())
					{
						if (rl.front() == kDirectorySeparator)
							return Std::Utf8String(tl + rl);
					}
					return tl + kDirectorySeparator + rl;
				}
				return rhs;
			}
			
			inline Std::Utf8String Combine(const Vector<Std::Utf8String>& dirs)
			{
				Std::Utf8String result;
				for (const auto& d : dirs)
				{
					result += d;
					result += '/';
				}
				return result;
			}

			inline Std::Utf8String ToOS(const Std::Utf8String& path)
			{
				Std::Utf8String result;
				for (auto c : path)
				{
					if (c == kDirectorySeparator)
						result += kOsDirectorySeparator;
					else
						result += c;
				}
				return result;
			}

			inline Std::Utf8String GetExtension(const Std::Utf8String& path)
			{
				const Std::Utf8String normalized = Normalize(path);
				auto it = Find(normalized.rbegin(), normalized.rend(), uint32_t(kExtensionSeparator));
				auto slash = Find(normalized.rbegin(), normalized.rend(), uint32_t(kDirectorySeparator));
				if ((slash != normalized.rend()) && (it < slash))
					return Std::Utf8String();
				if (it == normalized.rend())
					return Std::Utf8String();
				return Std::Utf8String(it.base() + 1, normalized.end());
			}

			inline bool HasFilename(const Std::Utf8String& path)
			{
				if (path.size() == 0 || path.back() == kDirectorySeparator)
					return false;
				return true;
			}

			inline Std::Utf8String RemoveFilename(const Std::Utf8String& path)
			{
				Std::Utf8String normalized = Normalize(path);
				if (HasFilename(normalized))
				{
					auto lastSep = Find(normalized.rbegin(), normalized.rend(), uint32_t(kDirectorySeparator));
					if (lastSep != normalized.rend())
						normalized.erase(lastSep.base() + 1, normalized.end());
					else
						normalized.clear();
				}
				return normalized;
			}

			inline Std::Utf8String GetFilenameAndExtension(const Std::Utf8String& path)
			{
				Std::Utf8String normalized = Normalize(path);
				if (normalized.empty())
					return Std::Utf8String();
				auto it = Find(normalized.rbegin(), normalized.rend(), uint32_t(kDirectorySeparator));
				if (it != normalized.rend())
					return Std::Utf8String(it.base() + 1, normalized.end());
				return Std::Utf8String();
			}

			inline Std::Utf8String RemoveRoot(const Std::Utf8String& path)
			{
				Std::Utf8String result = Normalize(path);
				
				// Is Windows style root.
				if (result.length() >= 2 && result.at(1) == ':')
				{
					result.erase(result.begin(), result.begin() + 2);
				}
				// Is it unix style rooted.
				else if (!result.empty() && result.at(0) == kDirectorySeparator)
					result.erase(result.begin(), result.begin() + 1);
				
				return result;
			}

			inline Std::Utf8String GetDirectory(const Std::Utf8String& path)
			{
				Std::Utf8String result = path;
				if (IsRooted(path.data()))
				{
					result = RemoveRoot(result.data());
				}
				return RemoveFilename(result.data());
			}

			//////////////////////////////////////////////////////////////////////////
			inline Vector<Std::Utf8String> Components(const Std::Utf8String& path)
			{
				Vector<Std::Utf8String> result;
				Std::Utf8String normalized = Normalize(path);
				Std::Utf8String current;
				
				for (const auto c : normalized)
				{
					if (c == kDirectorySeparator)
					{
						if (!current.empty())
							result.push_back(current);
						current.clear();
					}
					else
						current += c;
				}
				if (!current.empty())
					result.push_back(current);
				return result;
			}
		}
	}
}
