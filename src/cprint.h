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

/*
 * ANSI Escaped Code
 * Wikipedia: https://en.wikipedia.org/wiki/ANSI_escape_code
 */
#ifndef CUTILS_CPRINT_H
#define CUTILS_CPRINT_H

#define CSI				"\x1b["
#define _				";"
#define END				"m"

#define NML				"0"
#define BOLD			"1"
#define FAINT			"2"
#define ITALIC			"3"
#define UNDERLINE		"4"
#define SLOW_BLINK		"5"
#define RAPID_BLINK		"6"
#define REVERSE			"7"
#define CONCEAL			"8"
#define CROSSED_OUT		"9"
#define DEFAULT_FONT	"10"
// 11-19 Alternative font n-10

// eg: OFF UNDERLINE ==> "24"
#define OFF				"2"

#define FG_BLACK		"30"
#define FG_RED			"31"
#define FG_GREEN		"32"
#define FG_BROWN		"33"
#define FG_BLUE			"34"
#define FG_purple		"35"
#define FG_cyan			"36"
#define FG_GRAY			"37"
#define FG_RGB(R, G, B) "38;2;" R _ G _ B
#define FG_DEFAULT		"39"

#define BG_BLACK		"40"
#define BG_RED			"41"
#define BG_GREEN		"42"
#define BG_BROWN		"43"
#define BG_BLUE			"44"
#define BG_purple		"45"
#define BG_cyan			"46"
#define BG_GRAY			"47"
#define BG_RGB(R, G, B) "48;2;" R _ G _ B
#define BG_DEFAULT		"49"

#define OVERLINE		"53"

#define RESET CSI NML END

#define SGR(ATTR, str) CSI ATTR END str RESET

#endif
