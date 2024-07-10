#! /bin/sh

copyright_line="Copyright 2018-2019, 2024 mattmaniak, Jakub \"QooBooS\" Mieszczak"
kernel_name=$(uname -s)

for code_file in src/*; do
    grep -q "$copyright_line" "$code_file"

    if [ $? -ne 0 ]; then
        # https://stackoverflow.com/questions/9533679/how-to-insert-a-text-at-the-beginning-of-a-file
        case $kernel_name in
            "Darwin")
                sed -i "" "1s/^/\/\/ $copyright_line\n\n/" "$code_file"
            ;;
            "Linux")
                sed -i "1s/^/\/\/ $copyright_line\n\n/" "$code_file"
            ;;
        esac

        echo "Added a copyright line to ${code_file}."
    else
        echo "Copyright line is up-to-date in ${code_file}."
    fi
done
