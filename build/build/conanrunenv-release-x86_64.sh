script_folder="/home/blakeziegler/Tech/projects/ozone/Ozone-Blockchain/build/build"
echo "echo Restoring environment" > "$script_folder/deactivate_conanrunenv-release-x86_64.sh"
for v in OPENSSL_MODULES
do
    is_defined="true"
    value=$(printenv $v) || is_defined="" || true
    if [ -n "$value" ] || [ -n "$is_defined" ]
    then
        echo export "$v='$value'" >> "$script_folder/deactivate_conanrunenv-release-x86_64.sh"
    else
        echo unset $v >> "$script_folder/deactivate_conanrunenv-release-x86_64.sh"
    fi
done


export OPENSSL_MODULES="/home/blakeziegler/.conan2/p/b/opens69f132e0d17bd/p/lib/ossl-modules"