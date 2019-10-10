oj() {
  ext=${1##*.}
  if [ -z ext ]
  then
    echo 'Extension unspecified.'
    return 1
  fi

  filename=${1##*/}
  filename=${filename%.*} 
  case $ext in
    c   ) gcc -o "/tmp/$filename" "$1" && "/tmp/$filename" ;;
    cpp ) g++ -o "/tmp/$filename" "$1" && "/tmp/$filename" ;;
    java) javac "$1" -d /tmp/ && java -cp /tmp/ "$filename" ;;
    py  ) python3 "$1" ;;
    *   ) echo "Unknown extension name: $ext" ;;
  esac
}