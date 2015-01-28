user="youdaoyzbx%40163.com";
password="youdaoyzbx_123";
agent="User-Agent: Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:35.0) Gecko/20100101 Firefox/35.0";
base_url="https://note.wiz.cn";
login_url=$base_url"/api/login";
ref_url=$base_url"/login?p=login";

data="client_type=web2.0&api_version=4&token=&user_id=$user&password=$password";

curl -L -A '$agent' -d $data --url $login_url -D head.html -c cookie.html -o login.html;


data=`cat login.html`;
#"cookie_str":"f5e5ec055c865f1173f296f76850ccedcfa619f24618c452523097ef2aa582fd01107172a8ab8cb5a65f8990976d117c",
substr="/*cookie_str/";
data=${data##*cookie_str\":\"};
echo "data is ..............";
echo $data;
substr=",";
cache_str=${data%%\",*};

echo "cache_str is ..............";
echo $cache_str;
url=$base_url"/web";
curl -L -A '$agent' -b `cat login.html` --url $url -e $base_url -D head2.html -c cookie2.html -o login2.html;
