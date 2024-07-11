#! /bin/sh

license_file="LICENSE.txt"
copyright_line=$(sed '3q;d' ${license_file}) # Get third line.
kernel_name=$(uname -s)

echo "Copyright line from ${license_file} is\n${copyright_line}." 

if file "$license_file" | grep "CRLF"; then
    copyright_line=$(echo $copyright_line | tr -d "\r")
fi

for code_file in src/*; do
    if grep -q "$copyright_line" "$code_file"; then
        echo "Copyright line is up-to-date in ${code_file}."
    else
        if grep -iq "copyright" "$code_file"; then
            echo "Updating a copyright line in ${code_file}..."

            case $kernel_name in
                "Darwin")
                    sed -i "" "1d;2d" "$code_file"
                ;;
                "Linux")
                    sed -i "1d;2d" "$code_file"
                ;;
            esac
        fi

        case $kernel_name in
            "Darwin")
                sed -i "" "1s/^/\/\/ $copyright_line\n\n/" "$code_file"
            ;;
            "Linux")
                sed -i "1s/^/\/\/ $copyright_line\n\n/" "$code_file"
            ;;
        esac

        echo "Added an up-to-date copyright line to ${code_file}."
    fi
done
