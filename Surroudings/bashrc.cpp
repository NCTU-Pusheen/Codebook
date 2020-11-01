oj() {
  ext=${1##*.}            #空格敏感
  filename=${1##*/}       #空格敏感
  filename=${filename%.*} #空格敏感
  case $ext in
    cpp ) g++ -o "/tmp/$filename" "$1" && "/tmp/$filename" ;; #空格不敏感
    py  ) python3 "$1" ;;                                     #空格不敏感
  esac
}
