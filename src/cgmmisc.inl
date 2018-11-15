/* gph-cmath - C graphics math library
 * Copyright (C) 2018 John Tsiombikas <nuclear@member.fsf.org>
 *
 * This program is free software. Feel free to use, modify, and/or redistribute
 * it under the terms of the MIT/X11 license. See LICENSE for details.
 * If you intend to redistribute parts of the code without the LICENSE file
 * replace this paragraph with the full contents of the LICENSE file.
 */
static inline float cgm_deg_to_rad(float deg)
{
	return M_PI * deg / 180.0f;
}

static inline float cgm_rad_to_deg(float rad)
{
	return 180.0f * rad / M_PI;
}
