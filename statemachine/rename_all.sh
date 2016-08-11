for f in *.old; do
mv "$f" "$(basename "$f" .old)"
done
