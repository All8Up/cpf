//////////////////////////////////////////////////////////////////////////
#pragma once
#include "IO/IO.hpp"
#include "String.hpp"
#include "Vector.hpp"
#include "Algorithm.hpp"
#include "Std/CCType.hpp"


//////////////////////////////////////////////////////////////////////////
namespace Cpf
{
	namespace Platform
	{
		namespace IO
		{
			namespace Path
			{
				template<typename CHAR_TYPE>
				struct CPF_EXPORT_IO PathConstants
				{
					static const CHAR_TYPE kReversedSeparator;
					static const CHAR_TYPE kOsDirectorySeparator;
					static const CHAR_TYPE kDirectorySeparator;
					static const CHAR_TYPE kExtensionSeparator;
				};


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
						if (Std::IsSpace(*ibegin))
							continue;
						else
						{
							if (ibegin != result.begin())
								result.erase(result.begin(), ibegin);
							break;
						}
					}
					for (auto ibegin = result.rbegin(), iend = result.rend(); ibegin != iend; ++ibegin)
					{
						if (Std::IsSpace(*ibegin))
							continue;
						else
						{
							if (ibegin != result.rbegin())
								result.erase(ibegin.base(), result.end());
							break;
						}
					}

					Cpf::Replace(
						result.begin(),
						result.end(),
						PathConstants<typename STRING_TYPE::value_type>::kReversedSeparator,
						PathConstants<typename STRING_TYPE::value_type>::kDirectorySeparator);
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
					if (temp.size() >= 1 && temp.at(0) == PathConstants<typename STRING_TYPE::value_type>::kDirectorySeparator)
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

					auto it = temp.find_last_of(PathConstants<typename STRING_TYPE::value_type>::kExtensionSeparator);
					auto slash = temp.find_last_of(PathConstants<typename STRING_TYPE::value_type>::kDirectorySeparator);
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
						return STRING_TYPE(1, PathConstants<typename STRING_TYPE::value_type>::kDirectorySeparator);
					if (path.back() == PathConstants<typename STRING_TYPE::value_type>::kDirectorySeparator)
						return path;
					return path + PathConstants<typename STRING_TYPE::value_type>::kDirectorySeparator;
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
						if (tl.back() == PathConstants<typename STRING_TYPE::value_type>::kDirectorySeparator)
							return STRING_TYPE(tl + rl);
						else
						{
							if (!rl.empty())
							{
								if (rl.front() == PathConstants<typename STRING_TYPE::value_type>::kDirectorySeparator)
									return STRING_TYPE(tl + rl);
							}
							return tl + PathConstants<typename STRING_TYPE::value_type>::kDirectorySeparator + rl;
						}
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
					Cpf::Replace(
						result.begin(),
						result.end(),
						PathConstants<typename STRING_TYPE::value_type>::kDirectorySeparator,
						PathConstants<typename STRING_TYPE::value_type>::kOsDirectorySeparator
					);
					return result;
				}
				inline String ToOS(const String& path) { return _ToOS(path); }
				inline WString ToOS(const WString& path) { return _ToOS(path); }

				template<typename STRING_TYPE>
				STRING_TYPE _GetExtension(const STRING_TYPE& src)
				{
					const STRING_TYPE temp = Normalize(src);

					auto it = temp.find_last_of(PathConstants<typename STRING_TYPE::value_type>::kExtensionSeparator);
					auto slash = temp.find_last_of(PathConstants<typename STRING_TYPE::value_type>::kDirectorySeparator);
					if (it < slash || it == STRING_TYPE::npos)
						return STRING_TYPE();
					return STRING_TYPE(temp.begin() + it, temp.end());
				}
				inline String GetExtension(const String& path) { return _GetExtension(path); }
				inline WString GetExtension(const WString& path) { return _GetExtension(path); }


				template<typename STRING_TYPE>
				bool _HasFilename(const STRING_TYPE& src)
				{
					if (src.size() == 0 || src.back() == PathConstants<typename STRING_TYPE::value_type>::kDirectorySeparator)
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
						auto lastSep = result.find_last_of(PathConstants<typename STRING_TYPE::value_type>::kDirectorySeparator);
						result.erase(result.begin() + lastSep + 1, result.end());
					}
					return result;
				}
				inline String RemoveFilename(const String& path) { return _RemoveFilename(path); }
				inline WString RemoveFilename(const WString& path) { return _RemoveFilename(path); }

				template<typename STRING_TYPE>
				STRING_TYPE _GetFilename(const STRING_TYPE& src, bool withExtension)
				{
					// TODO: Add extension handling.
					CPF_ASSERT(withExtension == false); // Not implemented.
					(void)withExtension;

					STRING_TYPE norm = Path::Normalize(src);

					if (norm.empty())
						return STRING_TYPE();

					auto it = norm.find_last_of(PathConstants<typename STRING_TYPE::value_type>::kDirectorySeparator);
					if (it != STRING_TYPE::npos)
						return STRING_TYPE(norm.begin() + it + 1, norm.end());

					return STRING_TYPE();
				}
				inline String GetFilename(const String& path, bool we = false) { return _GetFilename(path, we); }
				inline WString GetFilename(const WString& path, bool we = false) { return _GetFilename(path, we); }

				template<typename STRING_TYPE>
				STRING_TYPE _RemoveRoot(const STRING_TYPE& path)
				{
					STRING_TYPE result = Normalize(path);

					// Is Windows style rooted.
					if (result.size() >= 2 && result.at(1) == ':')
						result.erase(result.begin(), result.begin() + 2);

					// Is it unix style rooted.
					else if (result.size() >= 1 && result.at(0) == PathConstants<typename STRING_TYPE::value_type>::kDirectorySeparator)
						result.erase(result.begin(), result.begin() + 1);

					return result;
				}
				inline String RemoveRoot(const String& path) { return _RemoveRoot(path); }
				inline WString RemoveRoot(const WString& path) { return _RemoveRoot(path); }

				template<typename STRING_TYPE>
				STRING_TYPE _GetDirectory(const STRING_TYPE& path)
				{
					STRING_TYPE result = path;
					if (IsRooted(path))
						result = RemoveRoot(result);
					return RemoveFilename(result);
				}
				inline String GetDirectory(const String& path) { return _GetDirectory(path); }
				inline WString GetDirectory(const WString& path) { return _GetDirectory(path); }

				//////////////////////////////////////////////////////////////////////////
				template<typename STRING_TYPE>
				Vector<STRING_TYPE> _Components(const STRING_TYPE& path)
				{
					Vector<STRING_TYPE> result;
					STRING_TYPE temp = Normalize(path);
					STRING_TYPE current;
					for (const auto c : temp)
					{
						if (c == PathConstants<typename STRING_TYPE::value_type>::kDirectorySeparator)
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
}
