avconv -r 23 -g 230 -s 1600x900 -f x11grab -i :0.0 -vcodec libx264 \
-threads 0 -preset fast -q 1 `date +%F-%H-%M-%S.x264.mkv`
