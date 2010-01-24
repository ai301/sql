// Copyright (c) 2010 Garrett R. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef SQL_UTILITY_H_
#define SQL_UTILITY_H_

#include <string>

#include <sqlite3.h>

namespace sql {

inline string printf(const std::string& fmt, ...) {
  char *tmp;
  std::string msg;
  va_list ap;

  va_start(ap, fmt);

  msg = tmp = sqlite3_vmprintf(fmt.c_str(), ap);
  sqlite3_free(tmp);

  va_end(ap);

  return msg;
}

/**
 * Escapes the string for use in sqlite
 *
 * @param  unescaped the unescaped string
 * @return escaped form of the unescaped string
 */
inline string escape(const std::string &unescaped) {
  std::string escaped;
  char *tmp;

  escaped = tmp = sqlite3_mprintf("%q", unescaped.c_str());
  sqlite3_free(tmp);

  return escaped;
}

/**
 * Quotes and escapes the string for use in sqlite
 *
 * @param  unquoted the unescaped string
 * @return quoted and escaped form of the unquoted string
 */
inline string quote(const string &unquoted) {
  std::string quoted;
  char *tmp;

  quoted = tmp = sqlite3_mprintf("%Q", unquoted.c_str());
  sqlite3_free(tmp);

  return quoted;
}

} // end namespace sql

#endif
