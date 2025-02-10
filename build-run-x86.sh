# Copyright (c) 2024- KanTV Authors
#!/bin/bash

set -e

PWD=`pwd`
LLAMA_CLI=llama-cli

function show_pwd()
{
    echo -e "current working path:$(pwd)\n"
}

function build_x86
{
    cmake -H. -B./out/x86 -DBUILD_SHARED_LIBS=OFF -DGGML_BACKEND_DL=OFF
    cd out/x86
    make -j16

    ls -lah bin/${LLAMA_CLI}
    /bin/cp -fv bin/${LLAMA_CLI} ../../${LLAMA_CLI}-x86
    cd -
}


function remove_temp_dir()
{
    if [ -d out ]; then
        echo "remove out directory in `pwd`"
        rm -rf out
    fi
}


function show_usage()
{
    echo "Usage:"
    echo "  $0 build"
    echo -e "\n\n\n"
}


show_pwd

if [ $# == 0 ]; then
    show_usage
    exit 1
elif [ $# == 1 ]; then
    if [ "$1" == "-h" ]; then
        show_usage
        exit 1
    elif [ "$1" == "help" ]; then
        show_usage
        exit 1
    elif [ "$1" == "build" ]; then
        build_x86
        exit 0
    fi
else
    show_usage
    exit 1
fi
