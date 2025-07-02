/*
Copyright (c) thiago, 2025

This file is part of .test/test.

.test/test is free software: you can redistribute it and/or modify
it under the terms of the GNU Affero General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

.test/test is distributed in the hope that it will be useful,
but WITHOUT ANY  WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS  FOR A PARTICULAR PURPOSE.  See the
GNU Affero General Public License for more  details.

You should have received a copy of the GNU Affero General Public License
along with .test/test. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef _game_h_
#define _game_h_

#include "weaver/weaver.h"
#include "includes.h"

struct _game_struct{
  // You can personalize this struct putting your variables here. But
  // don't change it's name. Access it in W.game variable.
  int whatever; // <- This variable is here to prevent compiler errors
};

extern struct _game_struct _game;

void main_loop(void);

#endif
