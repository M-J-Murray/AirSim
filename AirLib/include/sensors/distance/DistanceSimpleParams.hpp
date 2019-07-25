// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#ifndef msr_airlib_DistanceSimpleParams_hpp
#define msr_airlib_DistanceSimpleParams_hpp

#include "common/Common.hpp"
#include "common/AirSimSettings.hpp"


namespace msr { namespace airlib {


struct DistanceSimpleParams {
	real_T min_distance = 0.1; //cm
	real_T max_distance = 180; //cm
	real_T accuracy = 0.01; // Percentage
	real_T update_frequency = 10000; //Hz

	Pose relative_pose{
		Vector3r(0,0,0.19),					// x, y, z location
		VectorMath::toQuaternion(
			Utils::degreesToRadians(-90),	//pitch - rotation around Y axis
			Utils::degreesToRadians(0),		//roll  - rotation around X axis
			Utils::degreesToRadians(0)		//yaw   - rotation around Z axis
		)
	};

	real_T update_latency = 0.0f;    //sec
	real_T startup_delay = 0;        //sec

	void initializeFromSettings(const AirSimSettings::DistanceSetting& settings)
	{
		min_distance = settings.min_distance;
		max_distance = settings.max_distance;
		accuracy = settings.accuracy;
		update_frequency = settings.update_frequency;

		float x, y, z;
		x = !std::isnan(settings.position.x()) ? settings.position.x() : 0;
		y = !std::isnan(settings.position.y()) ? settings.position.y() : 0;
		z = !std::isnan(settings.position.z()) ? settings.position.z() : 0;
		relative_pose.position = Vector3r(x, y, z);

		float pitch, roll, yaw;
		pitch = !std::isnan(settings.rotation.pitch) ? settings.rotation.pitch : 0;
		roll = !std::isnan(settings.rotation.roll) ? settings.rotation.roll : 0;
		yaw = !std::isnan(settings.rotation.yaw) ? settings.rotation.yaw : 0;
		relative_pose.orientation = VectorMath::toQuaternion(
			Utils::degreesToRadians(pitch),   //pitch - rotation around Y axis
			Utils::degreesToRadians(roll),    //roll  - rotation around X axis
			Utils::degreesToRadians(yaw)	  //yaw   - rotation around Z axis
		);   
	}
};


}} //namespace
#endif
