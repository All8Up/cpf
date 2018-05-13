//////////////////////////////////////////////////////////////////////////
#pragma once
#include "CPF/Std/Vector.hpp"
#include "CPF/Std/Algorithm.hpp"
#include "CPF/CSTD/CCType.hpp"
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

			inline STD::Utf8String Normalize(const STD::Utf8String& path)
			{
				STD::Utf8String result;
				auto ibegin = path.begin();
				auto iend = path.end();
				if (ibegin == iend)
					return result;

				while (CSTD::IsSpace(*ibegin))
					++ibegin;
				while (CSTD::IsSpace(*(iend - 1)))
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

			inline bool IsRooted(const STD::Utf8String& path)
			{
				if (path.length() >= 2 && path.at(1) == ':')
					return true;
				if (!path.empty() && path.at(0) == kDirectorySeparator)
					return true;
				return false;
			}

			inline STD::Utf8String GetRoot(const STD::Utf8String& path)
			{
				if (IsRooted(path))
				{
					if (path.length() >= 2 && path.at(1) == ':')
						return STD::Utf8String(path.begin(), path.begin() + 2);
				}
				return STD::Utf8String();
			}

			inline bool HasExtension(const STD::Utf8String& path)
			{
				auto it = STD::Find(path.rbegin(), path.rend(), uint32_t(kExtensionSeparator));
				auto slash = STD::Find(path.rbegin(), path.rend(), uint32_t(kDirectorySeparator));
				return it!=path.rend() && it < slash;
			}

			inline STD::Utf8String EnsureTrailingSeparator(const STD::Utf8String& path)
			{
				if (path.empty())
					return STD::Utf8String("/");
				if (path.back() == kDirectorySeparator)
					return path;
				STD::Utf8String result = path;
				result += kDirectorySeparator;
				return result;
			}

			inline STD::Utf8String Combine(const STD::Utf8String& lhs, const STD::Utf8String& rhs)
			{
				const STD::Utf8String tl = Normalize(lhs);
				const STD::Utf8String rl = Normalize(rhs);
				
				if (!tl.empty())
				{
					if (tl.back() == uint32_t(kDirectorySeparator))
						return STD::Utf8String(tl + rl);
					if (!rl.empty())
					{
						if (rl.front() == kDirectorySeparator)
							return STD::Utf8String(tl + rl);
					}
					return tl + kDirectorySeparator + rl;
				}
				return rhs;
			}
			
			inline STD::Utf8String Combine(const STD::Vector<STD::Utf8String>& dirs)
			{
				STD::Utf8String result;
				for (const auto& d : dirs)
				{
					result += d;
					result += '/';
				}
				return result;
			}

			inline STD::Utf8String ToOS(const STD::Utf8String& path)
			{
				STD::Utf8String result;
				for (auto c : path)
				{
					if (c == kDirectorySeparator)
						result += kOsDirectorySeparator;
					else
						result += c;
				}
				return result;
			}

			inline STD::Utf8String GetExtension(const STD::Utf8String& path)
			{
				const STD::Utf8String normalized = Normalize(path);
				auto it = STD::Find(normalized.rbegin(), normalized.rend(), uint32_t(kExtensionSeparator));
				auto slash = STD::Find(normalized.rbegin(), normalized.rend(), uint32_t(kDirectorySeparator));
				if ((slash != normalized.rend()) && (it < slash))
					return STD::Utf8String();
				if (it == normalized.rend())
					return STD::Utf8String();
				return STD::Utf8String(it.base() + 1, normalized.end());
			}

			inline bool HasFilename(const STD::Utf8String& path)
			{
				if (path.size() == 0 || path.back() == kDirectorySeparator)
					return false;
				return true;
			}

			inline STD::Utf8String RemoveFilename(const STD::Utf8String& path)
			{
				STD::Utf8String normalized = Normalize(path);
				if (HasFilename(normalized))
				{
					auto lastSep = STD::Find(normalized.rbegin(), normalized.rend(), uint32_t(kDirectorySeparator));
					if (lastSep != normalized.rend())
						normalized.erase(lastSep.base() + 1, normalized.end());
					else
						normalized.clear();
				}
				return normalized;
			}

			inline STD::Utf8String GetFilenameAndExtension(const STD::Utf8String& path)
			{
				STD::Utf8String normalized = Normalize(path);
				if (normalized.empty())
					return STD::Utf8String();
				auto it = STD::Find(normalized.rbegin(), normalized.rend(), uint32_t(kDirectorySeparator));
				if (it != normalized.rend())
					return STD::Utf8String(it.base() + 1, normalized.end());
				return STD::Utf8String();
			}

			inline STD::Utf8String RemoveRoot(const STD::Utf8String& path)
			{
				STD::Utf8String result = Normalize(path);
				
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

			inline STD::Utf8String GetDirectory(const STD::Utf8String& path)
			{
				STD::Utf8String result = path;
				if (IsRooted(path.data()))
				{
					result = RemoveRoot(result.data());
				}
				return RemoveFilename(result.data());
			}

			//////////////////////////////////////////////////////////////////////////
			inline STD::Vector<STD::Utf8String> Components(const STD::Utf8String& path)
			{
				STD::Vector<STD::Utf8String> result;
				STD::Utf8String normalized = Normalize(path);
				STD::Utf8String current;
				
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
