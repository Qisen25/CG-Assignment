#pragma once

#include <string>

#define SVEN_SIZE 15
#define SHEEP_SIZE 9

//REFERENCE: textures are obtained from google images
const std::string sven_files[SVEN_SIZE] =
{
	"1_head.jpg",
	"2_collar.jpg",
	"3_body.jpg",
	"4_mouth.jpg",
	"5_rightEar.jpg",
	"6_leftEar.jpg",
	"7_tail.jpg",
	"8_rightFrontLeg.jpg",
	"9_leftFrontLeg.jpg",
	"10_rightBackLeg.jpg",
	"11_leftBackLeg.jpg",
	"12_jaw.jpg",
	"13_nose.jpg",
	"14_15_eye.jpg",
	"14_15_eye.jpg"
};

const std::string sheep_files[SHEEP_SIZE] =
{
	"1_body.jpg",
	"2_wool_head.jpg",
	"3_face_head.jpg",
	"4_face.jpg",
	"5_RF_leg.jpg",
	"6_LF_leg.jpg",
	"7_RB_leg.jpg",
	"8_LB_leg.jpg",
	"9_low_leg.jpg",
};

const std::string light_tool[] =
{
	"1_hilt.jpg",
	"2_light.jpg",
};

//modified version of cube vertices from learnopengl
//front ,back, left, right sides textures are going in the same direction now
//rather than before side of cube textures were rotated at different direction
const float same_side_box[] = {
    -0.5f, -0.5f, -0.5f, 0.0f,  0.0f, -1.0f, 0.0f, 0.0f,//back
     0.5f, -0.5f, -0.5f, 0.0f,  0.0f, -1.0f, 1.0f, 0.0f,
     0.5f,  0.5f, -0.5f, 0.0f,  0.0f, -1.0f, 1.0f, 1.0f,
     0.5f,  0.5f, -0.5f, 0.0f,  0.0f, -1.0f, 1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f, 0.0f,  0.0f, -1.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 0.0f,  0.0f, -1.0f, 0.0f, 0.0f,//use this for vertical uniform textures on the side

    -0.5f, -0.5f,  0.5f, 0.0f,  0.0f,  1.0f, 0.0f, 0.0f,
     0.5f, -0.5f,  0.5f, 0.0f,  0.0f,  1.0f, 1.0f, 0.0f,
     0.5f,  0.5f,  0.5f, 0.0f,  0.0f,  1.0f, 1.0f, 1.0f,
     0.5f,  0.5f,  0.5f, 0.0f,  0.0f,  1.0f, 1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f, 0.0f,  0.0f,  1.0f, 0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f, 0.0f,  0.0f,  1.0f, 0.0f, 0.0f, //front

    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f, 1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f, 1.0f, 1.0f, //side of left

     0.5f,  0.5f,  0.5f, 1.0f,  0.0f,  0.0f, 0.0f, 1.0f,
     0.5f,  0.5f, -0.5f, 1.0f,  0.0f,  0.0f, 1.0f, 1.0f,
     0.5f, -0.5f, -0.5f, 1.0f,  0.0f,  0.0f, 1.0f, 0.0f,
     0.5f, -0.5f, -0.5f, 1.0f,  0.0f,  0.0f, 1.0f, 0.0f,
     0.5f, -0.5f,  0.5f, 1.0f,  0.0f,  0.0f, 0.0f, 0.0f,
     0.5f,  0.5f,  0.5f, 1.0f,  0.0f,  0.0f, 0.0f, 1.0f,//right side

    -0.5f, -0.5f, -0.5f, 0.0f, -1.0f,  0.0f, 0.0f, 1.0f,
     0.5f, -0.5f, -0.5f, 0.0f, -1.0f,  0.0f, 1.0f, 1.0f,
     0.5f, -0.5f,  0.5f, 0.0f, -1.0f,  0.0f, 1.0f, 0.0f,
     0.5f, -0.5f,  0.5f, 0.0f, -1.0f,  0.0f, 1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f, 0.0f, -1.0f,  0.0f, 0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, -1.0f,  0.0f, 0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f, 0.0f,  1.0f,  0.0f, 0.0f, 1.0f,
     0.5f,  0.5f, -0.5f, 0.0f,  1.0f,  0.0f, 1.0f, 1.0f,
     0.5f,  0.5f,  0.5f, 0.0f,  1.0f,  0.0f, 1.0f, 0.0f,
     0.5f,  0.5f,  0.5f, 0.0f,  1.0f,  0.0f, 1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f, 0.0f,  1.0f,  0.0f, 0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f, 0.0f,  0.0f,  1.0f, 0.0f, 1.0f
};
