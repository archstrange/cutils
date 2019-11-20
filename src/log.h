// cutils: my c utils library
// Copyright (C) 2019  Qijian Zhang <arch.strange@foxmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#ifndef CUTILS_LOG_H
#define CUTILS_LOG_H

typedef struct Logger *Logger;

/// Create a new Logger
///
/// @appname: the name of your app
/// @storage_path: where to put log files, NULL or empty for default: ~/.log
///
/// Log files are separated per app: @storage_path/@appname/name.log
Logger Logger_new(const char *appname, const char *storage_path);

void Logger_free(Logger self);

#endif

