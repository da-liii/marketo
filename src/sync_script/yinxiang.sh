username="youdaoyzbx%40163.com";
echo $username;
password="Youdaoyzbx_123";
echo $password;

data="username=$username&password=$password&rememberMe=true&_sourcePage=cDgNWSVaNvriMUD9T65RG_YvRLZ-1eYO3fqfqRu0fynRL_1nukNa4gH1t86pc1SP&__fp=aUX0ZwllC-U3yWPvuidLz-TPR6I9Jhx8";
echo $data;

length=`echo $data|wc -c`;
length=`echo $length - 1|bc`;

loginUrl="https://app.yinxiang.com/HeaderLogin.action?login";

# 
#
#-D head.html -c cookie.html
#-o login.html
curl -L -H "Content-Length: $length" -A 'Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:35.0) Gecko/20100101 Firefox/35.0' -d $data --url $loginUrl -c cookie.html -o login.html;

stra='{"redirectUrl":"';
strb=`cat login.html`;
lena=${#stra};
lenb=${#strb};
length=`echo $lenb - $lena -2|bc`

url=${strb:$lena:$length};
echo $url;
agent='Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:35.0) Gecko/20100101 Firefox/35.0';
curl -L -A "$agent" --url $url -b cookie.html -o login2.html;

url="https://app.yinxiang.com/shard/s48/enweb/notestore";
data="7|0|8|https://app.yinxiang.com/webclient/|2CFE0B564362829D7028AD77F1A8802B|com.evernote.web.shared.GWTNoteStoreInterface|getNoteWithResultSpec|java.lang.String/2004016611|com.evernote.edam.notestore.NoteResultSpec/1363504058|19f0cdba-988a-4783-a20c-fcaa12b38ce8|[Z/1413617015|1|2|3|4|2|5|6|7|6|8|5|1|1|1|1|1|0|0|0|0|1|";
length=${#data};
file="login3.html";
curl -L -H "Content-Length: $length" -A "$agent" --url $url -b cookie.html -o $file;



