Movie Database
========
[숙제 페이지](http://soar.snu.ac.kr:8080/assignments/2/)

`MovieDB.java`, `Node.java` 두 파일을 고쳐야합니다. 기초적인 링크드리스트
구현체는 `MyLinkedList.java`를 참고하세요.

```bash
make                        # Build project
java MovieDatabaseConsole   # Run

make clean                  # Remove build results


# Testing
make
mv test/AssignmentGuide.class .
java -ea AssignmentGuide
java MovieDatabaseConsole < test/input > actual
diff actual test/output
rm actual
```

###### Contributors
- stania <stania.pe.kr@gmail.com>
- shurain <shurain@gmail.com>
- wookayin <wookayin@gmail.com>
- ipkn <ipknhama@gmail.com>
