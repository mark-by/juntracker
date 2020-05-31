server {
    listen 443 ssl http2;

    root /home/mark/juntracker.ru/;

    index index.html index.htm index.hginx-debian.html;

    server_name juntracker.ru www.juntracker.ru *.juntracker.ru;

    ssl_protocols TLSv1 TLSv1.1 TLSv1.2; # Dropping SSLv3, ref: POODLE
    ssl_certificate /etc/ssl/ssl/juntracker_ru/*_juntracker_ru.full.crt;
    ssl_certificate_key /etc/ssl/ssl/juntracker_ru/*_juntracker_ru.key;
    ssl_ciphers "RC4:HIGH:!aNULL:!MD5!kEDH";
    add_header Strict-Transport-Security 'max-age=604800';

    location /static/ {
        alias /home/mark/juntracker.ru/juntracker/bin/static/;
    }

    location /media/ {
        alias /home/mark/juntracker.ru/media/;
    }


    location / {
        proxy_pass        http://127.0.0.1:5000;
        proxy_redirect    off;
        add_header        Access-Control-Allow-Origin *;
        proxy_set_header  X-Real_IP $remote_addr;
        proxy_set_header  X-NginX-Proxy true;
        proxy_set_header  Host $http_host;
        proxy_set_header  Upgrade $http_upgrade;
        proxy_set_header  X-Forwarded-Host $server_name;
        proxy_set_header  P3P 'CP="ALL DSP COR PSAa PSDa OUR NOR ONL UNI COM NAV"';
        proxy_pass_header Set-Cookie;
        proxy_http_version 1.1;
        proxy_buffering    off;

        proxy_set_header Proxy "";
        #include /etc/nginx/proxy_headers.conf;
    }

}
