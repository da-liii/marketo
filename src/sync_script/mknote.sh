#{"noteid":"4N8FH~lbTS_a4M0tw000pa","version":"tfgOBksBAAA=","importance":"0","title":"hello world yzbx yzbx yzbx","categoryid":"4N8FH~kupdFpM72xU003et","tags":"","sourceurl":"","notecontent":"<p>hello world yzbx yzbx yzbx<br/></p>bbbbbbbbbbbbbbbbbbb","editorValue":"<p>hello world yzbx yzbx yzbx<br/></p>"}

#curl -L -X POST -d "noteid=4N8FH~lbTS_a4M0tw000pa&version=tfgOBksBAAA=&importance=0&title=hello world yzbx yzbx yzbx&categoryid=4N8FH~kupdFpM72xU003et&tags=&sourceurl=&notecontent=<p>hello world yzbx yzbx yzbx<br/></p>bbbbbbbbbbbbbbbbbbbaaaaaaaaaaaaaaaaaaaaaaaaaaxxxxxxxxllllltmstmstmstmstms&editorValue=<p>hello world yzbx yzbx yzbx<br/></p>" "https://note.sdo.com/my" -e "https://note.sdo.com/my" > out.html 

#POST /tool/delegate?url=http%3a%2f%2fpassport.note.sdo.com%2faccount%2floginresult%3ftype%3demail%26returnUrl%3dhttps%253a%252f%252fnote.sdo.com%252fmy email=yzb1627884766%40gmail.com&password=yzb2.71828&submit_type=ajax

# http://note.sdo.com/tool/delegate?url=http%3a%2f%2fpassport.note.sdo.com%2faccount%2floginresult%3ftype%3demail%26returnUrl%3dhttps%253a%252f%252fnote.sdo.com%252fmy

# curl -H "X-First-Name: Joe" http://192.168.0.1/

#HTTP/1.1 200 OK
#Cache-Control: private
#Content-Type: text/html; charset=utf-8
#Server: Microsoft-IIS/7.5
#X-AspNetMvc-Version: 3.0
#X-AspNet-Version: 4.0.30319
#Set-Cookie: returl=https://note.sdo.com/my; domain=.note.sdo.com; path=/
#Set-Cookie: .iNoteVisiting=web; domain=note.sdo.com; path=/
#X-Powered-By: ASP.NET
#P3P: CP=CAO PSA OUR
#Date: Thu, 22 Jan 2015 02:35:07 GMT
#Content-Length: 13599


baseurl="http://note.sdo.com"
loginurl="$baseurl/"
#curl -o root.html http://note.sdo.com

#curl -o my.html http://note.sdo.com/my

# post user:password wrong in {http://note.sdo.com,http://note.sdo.com/my,http://note.sdo.com/tool/delegate}
#curl -H "Content-Length: $length" -L -X POST -d "email=yzb1627884766%40gmail.com&password=yzb2.71828&submit_type=ajax" http://note.sdo.com/my -e $baseurl > my2.html


url="http://note.sdo.com/tool/delegate?url=http%3a%2f%2fpassport.note.sdo.com%2faccount%2floginresult%3ftype%3demail%26returnUrl%3dhttps%253a%252f%252fnote.sdo.com%252fmy";

data="email=yzb1627884766%40gmail.com&password=yzb2.71828&submit_type=ajax";

length=`echo $data|wc -c`;
length=`echo $length - 1|bc`;

curl -H "Content-Length: $length" -L -X POST -d $data $url -e $baseurl -D head.html -c cookie.html -o my2.html

myurl=$baseurl/my;
curl -b cookie.html -e $baseurl -L $myurl -D head2.html -c cookie2.html -o my3.html;

#otherurl="https://note.sdo.com/static/js/3rd/ueditor1.2/editor_all.js";
#otherfile="editor_all.js";
#curl -b cookie.html -e $myurl -L $otherurl -o $otherfile;

#otherurl="https://note-static.sdo.com/p?/static/css~global~note.reset_2379,css~global~note.pages.header_3149,css~3rd~j.ui.themes~note~menu.ui_1161,css~3rd~j.ui.themes~note~tag.ui_1161,css~3rd~j.ui.themes~base~j.ui.theme_1161,css~3rd~j.ui.themes~base~j.ui.core_1161,css~3rd~j.ui.themes~base~j.ui.button_1161,css~3rd~j.ui.themes~base~j.ui.dialog_1161,css~3rd~j.ui.themes~base~j.ui.datepicker_1161,css~3rd~j.ui.themes~note~note.ui_3631,css~3rd~prettify_1161,css~my~others_3631,css~my~note.tree_3631,css~my~note.list_2443,css~my~note.template_1161,css~my~note.edit_3631,css~my~note.preview_1922,css~my~note.youni_1161,css~my~rereset-editor_1161,js~mknote~share~main_1614.css";
#otherfile="

time="";
gettime(){
    a=`date +%N`;
    b=`date +%s`;
    time=$b`echo $a /1000000|bc`;
}

gettime
url="https://note.sdo.com/notecategory/list?_=$time";
file="categoryidList.html";
curl -b cookie.html -e $myurl -L $url -o $file;

gettime
url="https://note.sdo.com/resource/download/fe36f6b9-ff2c-4f3f-ae4c-c80963d6607c?_=$time";
file="download.html";
curl -b cookie.html -e $myurl -L $url -o $file;

#gettime
#url="https://note.sdo.com/notecategory/list?_=$time";
#file="list2.html";
#curl -b cookie.html -e $myurl -L $url -o $file;

#https://note.sdo.com/note/list?_=1421899098476
#https://note.sdo.com/resource/download/fe36f6b9-ff2c-4f3f-ae4c-c80963d6607c?_=1421899098486
#

#gettime
#url="https://note.sdo.com/notecategory/list?_=$time";
#file="list3.html";
#curl -b cookie.html -e $myurl -L $url -o $file;


#gettime
#url="https://note.sdo.com/note/create?_=$time";
#file="create.html";
#curl -b cookie.html -e $myurl -L $url -o $file;

#gettime
#url="https://note.sdo.com/note/list?_=$time";
#file="noteList.html";
#curl -b cookie.html -e $myurl -L $url -o $file;


#gettime
#url="http://note.sdo.com/plugin/clipperdata?_=$time";
#file="clipperdata.html";
#curl -b cookie.html -e $myurl -L $url -o $file;


#url="https://note.sdo.com/account/loginreward";
#file="loginreward.html";
#curl -b cookie.html -e $myurl -L $url -o $file;

#gettime
#url="https://note.sdo.com/note/preview/4N8FH~l9qCTpM700Q000DK?_=$time";
#file="preview.html";
#curl -b cookie.html -e $myurl -L $url -o $file;

#gettime
#url="https://note.sdo.com/note/content/4N8FH~l9qCTpM700Q000DK?password=1573"
#file="content.html";
#curl -b cookie.html -e $myurl -L $url -o $file;


#url="http://sync.note.sdo.com/v2/Meta/GetLastUpdateTime?r=2318393"
#file="updateTime.html";
#curl -b cookie.html -e $myurl -L $url -o $file;

#create note
#url="https://note.sdo.com/clicktrace?param=cate_note"
#file="cate_note.html";
#curl -b cookie.html -e $myurl -L $url -o $file;

#url="https://note.sdo.com/clicktrace?param=list_newnote"
#file="list_newnote.html";
#curl -b cookie.html -e $myurl -L $url -o $file;

#post data
#data="email=yzb1627884766%40gmail.com&password=yzb2.71828&submit_type=ajax";
#data="noteid＝&version=ACjT7XzH//8=&importance=0&title=haha&categoryid=4N8FH~kupdFpM72xU003et&tags=&sourceurl=&notecontent=lalala&editorValue=";
data='{"noteid":"","version":"ACjT7XzH//8=","importance":"0","title":"haha","categoryid":"4N8FH~kupdFpM72xU003es","tags":"","sourceurl":"","notecontent":"","editorValue":""}';
url="https://note.sdo.com/note/SaveWithVersion";
file="save.html";
length=`echo $data|wc -c`;
length=`echo $length - 1|bc`;

curl -H "Content-Length: $length" -b cookie.html -e $baseurl -X POST -d $data $url  -o $file;



 #{"noteid":"","version":"ACjT7XzH//8=","importance":"0","title":"noteb","categoryid":"4N8FH~kupdFpM72xU003es","tags":"","sourceurl":"","notecontent":"","editorValue":""}










# handbook url failed!
# /{version}/user/current
#url="http://sync.note.sdo.com/v1/user/current"
#file="user1.html";
#curl -b cookie.html -e $myurl -L $url -o $file;

#url="http://sync.note.sdo.com/v1.2/user/current"
#file="user2.html";
#curl -b cookie.html -e $myurl -L $url -o $file;

#url="http://sync.note.sdo.com/v2/user/current"
#file="user3.html";
#curl -b cookie.html -e $myurl -L $url -o $file;

# /{version}/note-category
# /{version}/note
# /{version}/note-attachment

#gettime
#url="https://note.sdo.com/notecategory/list?_=$time";
#file="list4.html";
#curl -b cookie.html -e $myurl -L $url -o $file;


#https://note.sdo.com/note/list?_=1421902341341
#https://note.sdo.com/note/list?_=1421902404111
#https://note.sdo.com/note/list?_=1421902442569
#https://note.sdo.com/note/list?_=1421902567749

#url="https://note.sdo.com/my#!note/list";
#file="list5.html";
#curl -b cookie.html -e $myurl -L $url -o $file;


#special link
# http://note.sdo.com/tool/delegate?url=http%3a%2f%2fpassport.note.sdo.com%2faccount%2floginresult%3ftype%3demail%26returnUrl%3dhttps%253a%252f%252fnote.sdo.com%252fmy
# http://note.sdo.com/plugin/clipperdata?_=1421982193091
# https://note.sdo.com/my
#所有笔记 https://note.sdo.com/note/list?_=1421982196615
#默认分类 https://note.sdo.com/note/list/4N8FH~kupdFpM72xU003es?_=1421986020944
# https://note.sdo.com/account/loginreward
# https://note.sdo.com/note/create?_=1421982197096
#所有分类 https://note.sdo.com/notecategory/list?_=1421982197710
# https://note.sdo.com/note/preview/4N8FH~l9qCTpM700Q000DK?_=1421986058192
# https://note.sdo.com/note/content/4N8FH~l9qCTpM700Q000DK?password=1573
# https://note.sdo.com/note/create/4N8FH~kupdFpM72xU003et?_=1422179118285
# https://note.sdo.com/my#!note/create/4N8FH~kupdFpM72xU003et
# https://note.sdo.com/clicktrace?param=list_newnote

#{"noteid":"","version":"ACjT7XzH//8=","importance":"0","title":"test","categoryid":"4N8FH~kupdFpM72xU003et","tags":"","sourceurl":"","notecontent":"go go go<br/>","editorValue":""}
#

#https://note.sdo.com/note/content/Z1NGB388776A8578D0FC074EA63462A2BBBD1D4C?password=1623
#https://note.sdo.com/note/content/4N8FH~l5xPtFM706Y0007E?password=1639
#https://note.sdo.com/note/content/Z1NG8278873C416AE613AF4F96CEBE2E6079757D?password=1762
#https://note.sdo.com/note/content/Z1NGB388776A8578D0FC074EA63462A2BBBD1D4C?password=6276
#https://note.sdo.com/note/content/Z1NG8278873C416AE613AF4F96CEBE2E6079757D?password=144
#


































