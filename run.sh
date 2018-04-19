#!/usr/bin/env sh

print_folder_list ()
{
	echo
	echo " Materials"
}

config=""
folder=""

if [ -z $1 ]
then
	echo "Choose an example to run."

	print_folder_list

	exit -1
elif [[ ! -d $1 ]]; then
	echo "Invalid directory. Choose from one of the following:"

	print_folder_list

	exit -1
else
	folder=$1
fi

if [[ -n "$2" ]]; then
	config=$2
else
	config="Release"
fi

if [ ! -d $folder/build ]
then
	cmake -H$folder -B$folder/build -G"Visual Studio 15 2017 Win64" -DCMAKE_PREFIX_PATH=/c/Qt/5.10.1/msvc2017_64/lib/cmake
fi

cmake --build $folder/build --config $config

./$folder/build/$config/render.exe

exit 0


