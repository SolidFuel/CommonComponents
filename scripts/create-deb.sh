#!/usr/bin/bash -x

set -e
set -x

# Assume we are sitting in build
top=$1
[ -z "$top" ] && top=..

scripts=$(dirname "$0")
scripts=$(cd "$scripts"; pwd)

if [ -z "$SF_PROJECT" ]; then
  eval $(${scripts}/project_vars.sh -exp sh)
fi

pkg=${SF_PROJ_LOWER}
pkg_src=${top}/packaging

dir=${pkg}_${SF_VERSION}_linux-amd64

rm -rf ${dir}
mkdir ${dir}

# VST3
mkdir -p ${dir}/usr/lib/vst3
cp -R ${SF_VST3_BUILD_PATH}/* ${dir}/usr/lib/vst3

# Control file
mkdir ${dir}/DEBIAN
${scripts}/expand_file.sh ${pkg_src}/debian/control > ${dir}/DEBIAN/control

mkdir -p ${dir}/usr/share/doc/${pkg}

# changelog
chng=${dir}/usr/share/doc/${pkg}/changelog

# two spaces at the end are important
outro=" -- SolidFuel <solidfuelplugins@gmail.com>  "

touch ${chng}

in_version=""
date_string=""

input="../docs/CHANGELOG.txt"
while IFS= read -r line
do
    if [[ "$line" =~ ^VERSION* ]]; then
        if [[ "$in_version" ]]; then
            echo "${outro}${date_string}" >> ${chng}
            echo "" >> ${chng}
        fi
        parts=( $line )
        if (( ${#parts[@]} != 3 )); then
            echo "ERROR: Malformed version line `${line}`"
            exit 1
        fi
        date_string=$(date -R -d ${parts[2]})
        echo "${pkg} (${parts[1]}) stable; urgency=low" >> $chng
        in_version=1
    elif [[ "$in_version" ]]; then
        echo "  ${line}" >> $chng
    else
        echo "ERROR: Malformed change log. Text seen before VERSION line"
        exit 1
    fi

done < "$input"

if [[ "$in_version" ]]; then
    echo "${outro}${date_string}" >> ${chng}
    echo "" >> ${chng}
fi

gzip --best --no-name ${dir}/usr/share/doc/${pkg}/changelog

# copyright
${scripts}/expand_file.sh ${pkg_src}/debian/copyright > ${dir}/usr/share/doc/${pkg}/copyright

# CREATE
dpkg-deb --root-owner-group --build ${dir}

# Output tie file name for other steps
[ -n "${GITHUB_OUTPUT}" ] && echo "deb_file=${dir}.deb" >> ${GITHUB_OUTPUT}
