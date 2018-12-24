# GPG V0.8

_Gear Profile Generator_

![2017-02-01 13-15-12](https://cloud.githubusercontent.com/assets/12775748/22495085/8a1546a0-e880-11e6-8302-089ae74e31b0.png)

* 설치본 다운로드 : [https://github.com/dymaxionkim/GPG/releases/tag/GPG_V0.8](https://github.com/dymaxionkim/GPG/releases/tag/GPG_V0.8)
* 설명서(PDF) : [https://dymaxionkim.github.io/GPG/README/GPG_V0.8_README.pdf](https://dymaxionkim.github.io/GPG/README/GPG_V0.8_README.pdf)


## 유의사항
* 한글 코드 : EUC-KR (Linux 환경에서 설치본 압축 해제시 유의활 것)
* 설치 환경
  - MS Windows XP, Vista, 7, 8, 8.1, 10
  - Wine (MS Windows 8) in Linux

## 버튼 설명

* 토글 버튼 "Input Method"
  - 파라미터 입력 방법을 결정.
  - Direct = 좌측 입력창을 사용하여 파라미터를 입력
  - File = 파라미터 파일을 읽어들여 입력

* Load Input File
  - 읽어들일 파라미터 파일을 선택

* Generate
  - 기어 형상 생성

* Save Profile
  - 생성된 기어 형상 데이타를 *.scr 파일로 저장

* Save Parameter
  - 편집한 파라미터들을 추후에 이용할 수 있도록 파라미터 파일로 저장

* Help
  - 본 창을 열어줌

* About ...
  - 그냥 함 넣어봤음

* Quit
  - 종료


## 파라미터 설명
* Resolution of Involute Curve
  - 기어 측벽 곡선을 몇 개로 분할할 것인지를 결정.
  - 자연수로 입력할 것.
  - 입력 한계 2 ~ 50

* Resolution of Fillet Curve
  - 이뿌리 필렛 곡선을 몇 개로 분할할 것인지를 결정.
  - 자연수로 입력할 것.
  - 입력 한계 2 ~ 50

* Module of Gear
  - 기어의 모듈
  - 양수의 부동소숫점으로 입력할 것
  - 입력 한계 0.5 ~ 10

* Addendum of Gear
  - 기어의 어덴덤 치수
  - mm단위
  - 양수의 부동소숫점으로 입력할 것
  - 입력 한계 0.1 ~ 10

* Dedendum of Gear
  - 기어의 어덴덤 치수
  - mm단위
  - 양수의 부동소숫점으로 입력할 것
  - 입력 한계 0.1 ~ 10

* Fillet Radius of Gear's Root
  - 기어 이뿌리 필렛의 반경, 또는 기어 창성 공구 첨단부의 둥글기 반경
  - mm단위
  - 양수의 부동소숫점으로 입력할 것
  - 입력 한계 0.1 ~ 5

* Pressure Angle
  - 기어의 압력각
  - Degree 단위
  - 양수의 부동소숫점으로 입력할 것
  - 입력 한계 1 ~ 90

* Offset Factor
  - 기어의 전위계수.
  - 0.0의 경우는 전위량이 전혀 없는 '표준 기어'
  - 조금씩 전위 계수를 높여 가면서 최적 형상을 찾을 수 있음
  - 기어 측벽의 언더컷 제거 용도로 사용하는 경우가 많음
  - 너무 수치를 높이면 이빨 두께가 얇아져 기어 이빨의 강도 저하됨
  - 양수의 부동소숫점으로 입력할 것
  - 입력 한계 0 ~ 1

* Number of Teeth
  - 기어 이빨 갯수
  - 입력 한계 4 ~ 100


## 프로그램 설명

* 프로그램 작성 의도
  - 공개된 기어 작도 프로그램이 희귀함
  - 공개된 기어 작도 프로그램의 대부분은 기능이 미약하고 세밀한 기어 작도가 불가능
  - CAD 시스템과 데이터 교환 원활할 것
  - 사출용 기어는 설계자가 기어 형상을 직접 작도해야 하는 경우가 있음

* 향후 계획
  - Pro-Engineer에 내장된 Pro-Program Tool을 적용하여 연동되도록 시도
  - Spur Gear 뿐만 아니라 다양한 형태의 기어를 자동으로 모델링 가능하도록 시도
  - 가능한 국제 기어 규격 표준 데이터 확보, 적용 (가능할지 미지수)
  - 더욱 엄밀한 기어 작도 Notation을 확보, 적용 (시간 관계상 ..  ㅜㅜ;)

* 참고 자료
  - 적용된 인볼류트 곡선 함수
    - [기술사 류재완씨가 공개한 수식 사용](https://cloud.githubusercontent.com/assets/12775748/22495094/96708464-e880-11e6-9dc4-5d5fe5519f59.png)
    - J.H. Kuang and Y. T. Yang, "An Estimate of Mesh Stiffness and Load Sharing Ratio of a Spur Gear Pair", International Power Transmission and Gearing Conference -Volume 1, DE-Vol.43-1, ASME 1992
  - 코딩 도구
    - MATLAB 7.0, MCC Translator, LCC Compiler
    - LabWindows/CVI  - ver7.1


* 적용된 기능 및 특성
  - 파라미터 파일 편집 기능
  - 그래픽 프로파일 출력
  - Autocad Script File로 출력, Autocad에서 자동 작도 가능


## 기어형상 설명

* 백래쉬 없음
  - 따라서 본 도구를 이용하여 생성된 기어는 이빨이 서로 딱딱 물리게 될 것입니다.
  - 백래쉬를 주기 위해서는 Autocad 상에서 Scale 또는 offset 명령어를 이용하여 적절히 조절해 주면 될 것 같습니다.

* 기어 이뿌리 부분의 필렛은 트로코이드 곡선 방정식을 이용
  - 구면형상의 일반 필렛은 아닙니다.
  - 이를 통하여 기어의 첨단부와 이뿌리 부분이 동작시 간섭되지 않으면서도 
  - 최대한 살두께를 보장하여 기어의 강도를 최적으로 높여줄 수 있습니다.

* 전위량 설정이 가능
  - 전위계수 변경을 통하여, 기어 이빨 형상을 조정해 줄 수 있습니다.
  - 따라서 기어 측면의 언더컷 등을 제거하는데 도움이 됩니다.

* 기어 형상 데이타 이용은...  Autocad의 script 명령어를 이용
  - Autocad 명령줄에서 script 명령어를 치면, 파일 선택 팝업창이 뜨는데...
  - 여기서 본 프로그램에서 저장한 기어 형상 데이타 파일을 찾아서 선택해 주면 스크립트가 실행됩니다.
  - 이때, Osnap 모드는 반드시 해제 상태여야 합니다.  
  - Osnap 모드가 활성화 된 상태에서는, 괴상한 모양이 그려져 버립니다.
  - Autocad 버그로 생각됩니다.  
  - Autocad r14까지는 이런 현상이 없었는데, 2000 이후 부터는 이런 현상이 발생한다고 합니다.


## History

* 20050425 : ver 0.5
  - 연산, 입출력 기능 구현
* 20050426 : ver 0.6
  - 그래프상에 설명 문자 표시 추가,
  - HELP 창의 크기 변경 기능 버그 수정,
  - 파라미터 파일 읽어들일 때 디그리-라디안 변환 관계 버그 수정
* 20050427 : ver 0.7
  - 화면 표시 Radius of Pitch 설명 문자 오류 수정,
  - .scr 스크립트 버전 표시 오류 수정
* 20060730 : ver 0.8
  - 파라미터 입력 한계를 재조정.
  - 파라미터 표시 정밀도를 소숫점 8자리까지 올림.
  - 외경 및 내경 원의 표시 오류 수정
  - 결과 스크립트 파일 출력시 압력각 표기 오류 수정
  - 전위계수 줄 경우에 피치원,외경원,내경원 표시 오류 수정

