MD 파일
=====================================

# [인용문]
* 인용문을 블록 형태로 추가할 수 있습니다.
* 예제)
```
> 블럭 인용 문자를 사용할 수 있다. 
> 이것은 인용문이다. - 작성자
>> 내부에 다시 한번 사용 가능하다. 이것은 이중 인용문이다
```
> 블럭 인용 문자를 사용할 수 있다. 
> 이것은 인용문이다. - 작성자
>> 내부에 다시 한번 사용 가능하다. 이것은 이중 인용문이다. -


---

# 표현
* *기울여 쓰기*
* _기울여 쓰기_
* __굵게 쓰기__
* ~~취소선~~
* <u>밑줄</u>

* <span style="color:red">빨간색</span>
* <span style="color:#00FF00">Green</span>
* (`#`을 넣은 뒤 16진수로 R, G, B 값을 입력해서 지정할 수 있다.)
* <span style="color:rgb(0, 255, 0)">rgb(245, 235, 13)</span>
---


# [코드 블럭]
* 인라인 코드를 작성
* 여러줄의 코드를 작성 할 때는 ｀ 기호 또는 ~를 세번 쓴 코드 블럭을 사용 할 수 있습니다.
* 코드에 하이라이트를 넣으려면 ｀｀｀기호 뒤에 언어 이름을 쓰면 됩니다.
* 인라인 코드 <br/>
`인라인 코드 표현 시`
`void function(){}`
* 인라인 C언어
***
#### 예제2
```C++
#ifdef _DEBUG
  {
    Serial.print(frequency);
    delay(500);
  }
#endif
```
~~~cpp
블럭으로 표현 시
void function(){}
~~~
* 인라인 파이썬
```python
또는 물결로도 표시 가능
def function():
	pass
```

---
<p align="center">
  <br><a href="README.md">한글가능</a> | English | <a href="README.md">파일열기</a>
  <br>1111
  <br>2222
</p>

# 이미지
<p align="center">
  <a href="/img/1.jpg" target="_blank"><img  style="width: 250px; height: 54px;" width="250" height="54" /></a>
<br>
</p>


1. 이미지만 삽입할 경우
![이미지](이미지 링크)

2. 사이즈를 조절할 경우 - HTML 태그로 처리
<img src=이미지링크 width="450px" or "40%" height="300px" title="크기변경">
(velog에서는 사이즈 변경은 반영이 안되는거 같네요...)

3. 이미지 삽입 후 링크 걸기
[![이미지](링크)](연결할 링크)
결과


#### Latest release [![Latest release](https://img.shields.io/github/release/esp8266/Arduino.svg)](https://github.com/esp8266/Arduino/releases/latest/)

# [목록]
```
- 순서가 필요 없이 점으로 목록 생성 시
  * -, *, + 기호가 사용 가능
  + 들여쓰면 서브목록을 붙일 수 있음
    - 두 칸을 띄어쓰면
    + 서브 목록을 붙일 수 있음
```
---
### [메뉴3]
* [ ] 사각
* [ ] 사각
* [ ] 사각
---
### [메뉴4]
1. 숫자
2. 숫자
---

# 링크
인라인 링크, url링크, 참조링크 기능을 활용해 웹페이지 주소, 이메일 주소를 추가할 수 있습니다.

### [사용법]
* 참조링크 - [id]: URL "Option Title"
* 인라인 - [Title](Link)
* url링크: <URL/>, E-mail: <abc@abc.com>
### [예시]
* [Google] https://www.google.com "Google Link"
* [Google](https://www.google.com)
* [Google] <https://www.google.com/>
* <email@abc.com>

---
### 빈칸
* 문장 1
(빈 줄)
* 문장 2<br/><br/>
* 또는 마지막에   
* 세 칸 이상 띄우기
---


# [표 삽입]
* 간단한 표 생성이 가능하고, 표 안에서는 폰트 스타일을 적용할 수 있습니다.
또한 왼쪽, 가운데, 오른쪽 정렬 적용이 가능합니다.

* 사용법
| 기호로 셀을 구분하며 작성할 수 있으며 2.강조 에서 설명했던 글꼴 사용이 가능
하이픈(-)과 세미콜론(:)을 이어붙이면 오른쪽, 왼쪽, 가운데 정렬이 가능
```
| 표 | 셀1 | 셀2 |
|:-|:-:|-:|
|왼쪽 정렬|가운데정렬|오른쪽정렬|
```
| 표 | 셀1 | 셀2 |
|:-|:-:|-:|
|왼쪽 정렬|가운데정렬|오른쪽정렬|


# [체크박스]
* -, *, + 뒤에 한칸 띄어쓴 후 대괄호([, ])를 추가하면 체크박스 생성이 가능합니다.
* 대괄호([ ]) 사이에 x를 넣으면 체크된 체크박스가 생성됩니다.

* 사용법
```
- [ ] 공부
* [x] 놀기
```
- [ ] 공부
* [x] 놀기
---


# [즐겨찾기]
* https://velog.io/@woojinn8/Practice-Markdown-%EB%AC%B8%EB%B2%95-%EC%A0%95%EB%A6%AC