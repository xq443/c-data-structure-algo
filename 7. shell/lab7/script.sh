#! /usr/bin/bash

folder_name="lab7"
src=~/course_resources/course_resources/starter_code/labs
des=~/data_strctures/lab7/lab07_test

# Go to the dir where the "resources" repo for class lives locates
cd "$src"

# # Run a "git pull" to pull any new resources
git pull

# Check if the specified folder_name exists
# if [ -d "$folder_name" ]
# then
#     echo "Folder $folder_name already exists."
#     echo "Exist"
#     exit 0
# fi

# Check if the specified folder exists
if [ -d "$folder_name" ]
then
    # Prompt user input
    read -p "Do you want to copy the folder $folder_name? (y/n): " response
    if [[ "$response" == [yY] ]]
    then
        # Create destination directory if it doesn't exist
        mkdir -p "$des"
        # Copy the specified folder to the destination directory
        cp -r "$folder_name" "$des"
        echo "Copied folder $folder_nameder from 'resources' to '$des'."
    else
        echo "Folder $folder_name was not copied."
    fi
else
    echo "Folder $folder_name does not exist in 'resources'."
fi


