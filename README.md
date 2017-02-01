# GPG V0.8

_Gear Profile Generator_

![2017-02-01 13-15-12](https://cloud.githubusercontent.com/assets/12775748/22495085/8a1546a0-e880-11e6-8302-089ae74e31b0.png)

* 설치본 다운로드 : https://github.com/dymaxionkim/GPG/releases/tag/GPG_V0.8
* 설명서(PDF) : https://dymaxionkim/github.io/GPG/README/GPG_V0.8_README.pdf


## 유의사항
* 한글 코드 : EUC-KR
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



