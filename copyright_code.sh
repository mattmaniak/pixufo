#! /bin/sh

license_file="LICENSE.txt"
copyright_line=$(sed '3q;d' ${license_file}) # Get third line.
kernel_name=$(uname -s)

echo "Copyright line from ${license_file} is\n${copyright_line}." 

if file "$license_file" | grep "CRLF"; then
    copyright_line=$(echo $copyright_line | tr -d "\r")
fi

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
