// color.cpp - Utility functions for color conversion
// Copyright (C) 2018 Benjamin Lewis

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include "color.hpp"

dvec3 hsl2rgb(dvec3 input){
    // Adjust values for range
    double H = fmod(input[0],360.0)/60.0;
    double S = min(max(input[1],0.0),100.0)/100.0;
    double L = min(max(input[2],0.0),100.0)/100.0;

    // Create variables
    double C = (1.0 - fabs(2 * L - 1.0)) * S;
	double X = C * (1.0 - fabs(fmod(H, 2) - 1.0));
	double m = 1.0 * (L - 0.5 * C);

    dvec3 output(m, m, m);

	if(H < 1.0){
		output[0] += C; output[1] += X;
	}else 
    if(H < 2.0){
		output[0] += X; output[1] += C;
	}else 
    if(H < 3.0){
		output[1] += C; output[2] += X;
	}else 
    if(H < 4.0){
		output[1] += X; output[2] += C;
	}else 
    if(H < 5.0){
		output[0] += X; output[2] += C;
	}else 
    if(H < 6.0){
		output[0] += C; output[2] += X;
	}

    return output;
}