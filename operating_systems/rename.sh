for dir in *; do
    if [[ $dir =~ ^homework ]]; then
        new_dir=$(echo $dir | awk -F "_" '{print "hw_"$2}')
        mv $dir $new_dir
    fi
done