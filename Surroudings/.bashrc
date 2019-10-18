oj() {
  ext=${1##*.}
  filename=${1##*/}
  filename=${filename%.*}
  case $ext in
    c   ) gcc -o "/tmp/$filename" "$1" && "/tmp/$filename" ;;  # Omit this line if C is not needed
    cpp ) g++ -o "/tmp/$filename" "$1" && "/tmp/$filename" ;;
    java) javac "$1" -d /tmp/ && java -cp /tmp/ "$filename" ;; # Omit this line if Java is not needed
    py  ) python3 "$1" ;;
  esac
}
