//////////////////////////////////////////////////////////////////////////
#pragma once
#include "CPF/IO.hpp"
#include "CPF/Std/String.hpp"
#include "CPF/Std/Vector.hpp"
#include "CPF/Std/Algorithm.hpp"
#include "CPF/Std/CCType.hpp"
#include "CPF/Std/Utf8String.hpp"

//////////////////////////////////////////////////////////////////////////
namespace CPF
{
	namespace IO
	{
		// TODO: Strip this down and use only utf8.
		namespace Path
		{
#if CPF_TARGET_WINDOWS
			static constexpr char kReversedSeparator = '\\';
			static constexpr char kOsDirectorySeparator = '\\';
			static constexpr char kDirectorySeparator = '/';
			static constexpr char kExtensionSeparator = '.';
#endif

			/**
				* @brief Normalizes the given path.
				* @tparam STRING_TYPE The string type.
				* @param path The path to be normalized.
				* @return The normalized path.
				*/
			template<typename STRING_TYPE>
			STRING_TYPE _Normalize(const STRING_TYPE& path)
			{
				STRING_TYPE result = path;

				for (auto ibegin = result.begin(), iend = result.end(); ibegin != iend; ++ibegin)
				{
					if (!Std::IsSpace(*ibegin))
					{
						if (ibegin != result.begin())
							result.erase(result.begin(), ibegin);
						break;
					}
				}
				for (auto ibegin = result.rbegin(), iend = result.rend(); ibegin != iend; ++ibegin)
				{
					if (!Std::IsSpace(*ibegin))
					{
						if (ibegin != result.rbegin())
							result.erase(ibegin.base(), result.end());
						break;
					}
				}

				CPF::Replace(
					result.begin(),
					result.end(),
					kReversedSeparator,
					kDirectorySeparator);
				return result;
			}
			inline String Normalize(const String& path) { return _Normalize(path); }
			inline WString Normalize(const WString& path) { return _Normalize(path); }

			/**
				* @brief Determines if the given path is rooted.
				* @tparam STRING_TYPE The string type.
				* @param path The path to check.
				* @return true if rooted, false if not.
				*/
			template<typename STRING_TYPE>
			bool _IsRooted(const STRING_TYPE& path)
			{
				const STRING_TYPE temp = Normalize(path);

				// Is Windows style rooted.
				if (temp.size() >= 2 && temp.at(1) == ':')
					return true;

				// Is it unix style rooted.
				if (!temp.empty() && temp.at(0) == kDirectorySeparator)
					return true;

				return false;
			}
			inline bool IsRooted(const String& path) { return _IsRooted(path); }
			inline bool IsRooted(const WString& path) { return _IsRooted(path); }


			template<typename STRING_TYPE>
			STRING_TYPE _GetRoot(const STRING_TYPE& path)
			{
				const STRING_TYPE temp = Normalize(path);

				if (IsRooted(temp))
				{
					// Is Windows style rooted.
					if (temp.size() >= 2 && temp.at(1) == ':')
						return STRING_TYPE(temp.begin(), temp.begin() + 2);
				}
				return STRING_TYPE();
			}
			inline String GetRoot(const String& path) { return _GetRoot(path); }
			inline WString GetRoot(const WString& path) { return _GetRoot(path); }

			/**
				* @brief Determine if the path has an extension.
				* @tparam STRING_TYPE The string type.
				* @param path Path to check.
				* @return true if extension, false if not.
				*/
			template<typename STRING_TYPE>
			bool _HasExtension(const STRING_TYPE& path)
			{
				const STRING_TYPE temp = Normalize(path);

				auto it = temp.find_last_of(kExtensionSeparator);
				auto slash = temp.find_last_of(kDirectorySeparator);
				if (it < slash)
					return false;
				return it != STRING_TYPE::npos;
			}
			inline bool HasExtension(const String& path) { return _HasExtension(path); }
			inline bool HasExtension(const WString& path) { return _HasExtension(path); }

			template<typename STRING_TYPE>
			STRING_TYPE _EnsureTrailingSeparator(const STRING_TYPE& path)
			{
				if (path.empty())
					return STRING_TYPE(1, kDirectorySeparator);
				if (path.back() == kDirectorySeparator)
					return path;
				return path + STRING_TYPE::value_type(kDirectorySeparator);
			}
			inline String EnsureTrailingSeparator(const String& path) { return _EnsureTrailingSeparator(path); }
			inline WString EnsureTrailingSeparator(const WString& path) { return _EnsureTrailingSeparator(path); }

			/**
				* @brief Combines two paths together.
				* @tparam STRING_TYPE The string type.
				* @param lhs The left hand path.
				* @param rhs The right hand path.
				* @return A STRING_TYPE.
				*/
			template<typename STRING_TYPE>
			STRING_TYPE _Combine(const STRING_TYPE& lhs, const STRING_TYPE& rhs)
			{
				const STRING_TYPE tl = Normalize(lhs);
				const STRING_TYPE rl = Normalize(rhs);

				if (!tl.empty())
				{
					if (tl.back() == kDirectorySeparator)
						return STRING_TYPE(tl + rl);
					if (!rl.empty())
					{
						if (rl.front() == kDirectorySeparator)
							return STRING_TYPE(tl + rl);
					}
					return tl + STRING_TYPE::value_type(kDirectorySeparator) + rl;
				}
				return rhs;
			}
			inline String Combine(const String& lhs, const String& rhs) { return _Combine(lhs, rhs); }
			inline WString Combine(const WString& lhs, const WString& rhs) { return _Combine(lhs, rhs); }

			inline String Combine(const Vector<String>& dirs)
			{
				String result;
				for (const auto& d : dirs)
				{
					result += d;
					result += '/';
				}
				return result;
			}
			inline WString Combine(const Vector<WString>& dirs)
			{
				WString result;
				for (const auto& d : dirs)
				{
					result += d;
					result += L'/';
				}
				return result;
			}

			/**
				* @brief Converts a path to an operating system path.
				* @tparam STRING_TYPE The string type.
				* @param path Path to convert.
				* @return path as a STRING_TYPE.
				*/
			template<typename STRING_TYPE>
			STRING_TYPE _ToOS(const STRING_TYPE& path)
			{
				STRING_TYPE result = path;
				CPF::Replace(
					result.begin(),
					result.end(),
					kDirectorySeparator,
					kOsDirectorySeparator
				);
				return result;
			}
			inline String ToOS(const String& path) { return _ToOS(path); }
			inline WString ToOS(const WString& path) { return _ToOS(path); }

			template<typename STRING_TYPE>
			STRING_TYPE _GetExtension(const STRING_TYPE& src)
			{
				const STRING_TYPE temp = Normalize(src);

				auto it = temp.find_last_of(kExtensionSeparator);
				auto slash = temp.find_last_of(kDirectorySeparator);
				if ((slash != STRING_TYPE::npos) && (it < slash))
					return STRING_TYPE();
				if (it == STRING_TYPE::npos)
					return STRING_TYPE();
				return STRING_TYPE(temp.begin() + it + 1, temp.end());
			}
			inline String GetExtension(const String& path) { return _GetExtension(path); }
			inline WString GetExtension(const WString& path) { return _GetExtension(path); }


			template<typename STRING_TYPE>
			bool _HasFilename(const STRING_TYPE& src)
			{
				if (src.size() == 0 || src.back() == kDirectorySeparator)
					return false;
				return true;
			}
			inline bool HasFilename(const String& path) { return _HasFilename(path); }
			inline bool HasFilename(const WString& path) { return _HasFilename(path); }

			template<typename STRING_TYPE>
			STRING_TYPE _RemoveFilename(const STRING_TYPE& path)
			{
				STRING_TYPE result = Normalize(path);
				if (HasFilename(path))
				{
					auto lastSep = result.find_last_of(kDirectorySeparator);
					if (lastSep != STRING_TYPE::npos)
						result.erase(result.begin() + lastSep + 1, result.end());
					else
						result.clear();
				}
				return result;
			}
			inline String RemoveFilename(const String& path) { return _RemoveFilename(path); }
			inline WString RemoveFilename(const WString& path) { return _RemoveFilename(path); }

			inline Std::Utf8String GetFilenameAndExtension(const Std::Utf8String& path)
			{
				Std::Utf8String normalized = Normalize(path.data());
				if (normalized.empty())
					return Std::Utf8String();
				auto it = FindLast(normalized.begin(), normalized.end(), kDirectorySeparator);
				if (it != normalized.end())
					return Std::Utf8String(it, normalized.end());
				return Std::Utf8String();
			}

			inline Std::Utf8String RemoveRoot(const Std::Utf8String& path)
			{
				Std::Utf8String result = Normalize(path.data());
				
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
			inline Vector<Std::Utf8String> x_Components(const Std::Utf8String& path)
			{
				Vector<Std::Utf8String> result;
				// TODO: Normalize needs to be Utf8...
				Std::Utf8String normalized = Normalize(path.data());
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
			
			template<typename STRING_TYPE>
			Vector<STRING_TYPE> _Components(const STRING_TYPE& path)
			{
				Vector<STRING_TYPE> result;
				STRING_TYPE temp = Normalize(path);
				STRING_TYPE current;
				for (const auto c : temp)
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
			inline Vector<String> Components(const String& path) { return _Components(path); }
			inline Vector<WString> Components(const WString& path) { return _Components(path); }
		}
	}
}
