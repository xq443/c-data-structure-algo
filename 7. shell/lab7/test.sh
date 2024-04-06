#! /usr/bin/bash
# test

# echo "hello world"

# variable
# echo Our shell name is $BASH
# echo Our shell version is $BASH_VERSION
# echo Our home dir is $HOME
# echo Our current workin dir is $PWD

# val=10
# name=Mark
# echo The name is $name
# echo value $val

# pass arguments
# echo "Enter name : "
# read name1 name2 name3
# echo "Entered name : $name1  $name2 $name3"

# read -p 'username : ' user_val
# read -sp 'password : ' pass_val
# echo
# echo "username: $user_val"
# echo "password: $pass_val"

# echo "enter name: "
# read -a names
# echo "names : ${names[0]}, ${names[1]}"

# echo "enter name: "
# read 
# echo "names : $REPLY"

# echo $0 $1  '  > echo $0 $1'

# args={"$@"}

# echo $@
# echo $#

# if statement
# word=a
# if [[ $word == "b" ]]
# # if (($count > 9))
# then
#     echo "condition b is true"
# elif [[ $word == "a" ]]
# then    
#     echo  "condition a is true"
# else 
#     echo "condition is false"
# fi

# file test operator
echo -e "enter the name of the file : \c" # -e file exist or not
# -f if it is file or not
# -d  dir exist or not
# -s check file is empty or not
# -r -w -x if file has read / write / execute permission
read file_name 

if [ -d $file_name ]
then
    echo "$file_name found"
else
    echo "$file_name not found"
fi