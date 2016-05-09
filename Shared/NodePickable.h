#pragma once

enum nodePickable
{
	NOT_PICKABLE = 0,
	IS_PICKABLE = 1 << 0,
	IS_SHOOTABLE = 1 << 1,
};