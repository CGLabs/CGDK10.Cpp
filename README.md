# CGDK10.Cpp
어마어마한 성능과 안정성을 모두 가진 요구하는 게임 서버를 개발할 수 있는 게임 엔진 모듈입니다.<br/>
(game server engine with Ultra performance ans Stablilty)<br/>
<br/>

# Platform
 - windows<br/>
 - linux (centos, ubuntu)<br/>
<br/>

# directory
/include<br/>
header 파일들 입니다.<br/>
<br/>
/lib<br/>
lib(라이브러리) 파일들입니다. <br/>
/lib/cgdk/sdk10 폴터 아래에 windows, ubuntu, centos 용으로 구분해 저장되어 있습니다.<br/>
<br/>
/tutorial<br/>
예제 프로젝트들 입니다.<br/>
<br/>
/example<br/>
예제 프로젝트들입니다.<br/>
<br/>
/dll<br/>
mfc control용 dll들로 windows에서 CGCII의 mfc control들을 사용해서 제작하시면 필요합니다.<br/>
<br/>
<br/>



# compile

cmake설정

## include directories
>   INCLUDE_DIRECTORIES(<CGDK10 folder>/include)

## lib directories
>   LINK_DIRECTORIES(<CGDK10 folder>/lib/cgdk/sdk10/ubuntu)

<br/>
<br/>

## tutorials & examples 
### windows
Release<br/>
> build.Release.bat<br/>

Debug<br/>
> build.Debug.bat
<br/>

### ubuntu
Release<br/>
> cmake . -DCMAKE_BUILDE_TYPE=Release -DDIST=ubuntu<br/>

Debug<br/>
> cmake . -DCMAKE_BUILDE_TYPE=Debug -DDIST=ubuntu<br/>

<br/>

### centos
Release<br/>
>cmake . -DCMAKE_BUILDE_TYPE=Release -DDIST=centos<br/>

Debug<br/>
>cmake . -DCMAKE_BUILDE_TYPE=Debug -DDIST=centos<br/>
