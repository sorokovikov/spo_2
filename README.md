# СПО 2
ЛР 2 по дисциплине Системное программное обеспечение.

## Описание
Клиент: считывает пользовательские сообщения из стандартного ввода и отправляет их серверу.

Сервер: принимает сообщения от клиента и печатает их в стандартный вывод.

## Using
Сначала необходимо скомпилировать Клиент и Сервер. Для этого запустим скрипт:
```
$ bash build_app.sh
```
Далее последовательно запускаем в разных термниалах Сервер и Клиент:
```
$ ./server.out
```
```
$ ./client.out
```
Вводим сообщение в терминале с Клиентом:
```
$ ./client.out
Send message: Hello everyone!
```
Терминал с Сервером:
```
$ ./server.out
Thu Mar 25 19:31:34 2021
System: Start chat

Thu Mar 25 19:32:03 2021
Hello everyone!
```
