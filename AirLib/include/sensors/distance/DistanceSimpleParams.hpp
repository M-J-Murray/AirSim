// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#ifndef msr_airlib_DistanceSimpleParams_hpp
#define msr_airlib_DistanceSimpleParams_hpp

#include "common/Common.hpp"
#include "common/AirSimSettings.hpp"


namespace msr { namespace airlib {


struct DistanceSimpleParams {
	real_T min_distance = 0.1f; // meters
	real_T max_distance = 180.0f; // meters
	real_T accuracy = 0.01f; // Percentage
	uint update_frequency = 10000; //Hz

	Pose relative_pose{
		Vector3r(0, 0, 0.19f),					// x, y, z location
		VectorMath::toQuaternion(
			Utils::degreesToRadians(-90.0f),	//pitch - rotation around Y axis
			Utils::degreesToRadians(0.0f),		//roll  - rotation around X axis
			Utils::degreesToRadians(0.0f)		//yaw   - rotation around Z axis
		)
	};

	real_T update_latency = 0.0f;    //sec
	real_T startup_delay = 0.0f;     //sec

	void initializeFromSettings(const AirSimSettings::DistanceSetting& settings)
	{
		min_distance = settings.min_distance * 100; // Convert to cm
		max_distance = settings.max_distance * 100; // Convert to cm
		accuracy = settings.accuracy;
		update_frequency = settings.update_frequency;

		float x, y, z;
		x = !std::isnan(settings.position.x()) ? settings.position.x() : 0.0f;
		y = !std::isnan(settings.position.y()) ? settings.position.y() : 0.0f;
		z = !std::isnan(settings.position.z()) ? settings.position.z() : 0.19f;
		relative_pose.position = Vector3r(x, y, z);

		float pitch, roll, yaw;
		pitch = !std::isnan(settings.rotation.pitch) ? settings.rotation.pitch : -90.0f;
		roll = !std::isnan(settings.rotation.roll) ? settings.rotation.roll : 0.0f;
		yaw = !std::isnan(settings.rotation.yaw) ? settings.rotation.yaw : 0.0f;
		relative_pose.orientation = VectorMath::toQuaternion(
			Utils::degreesToRadians(pitch),   //pitch - rotation around Y axis
			Utils::degreesToRadians(roll),    //roll  - rotation around X axis
			Utils::degreesToRadians(yaw)	  //yaw   - rotation around Z axis
		);   
	}
};


}} //namespace
#endif
