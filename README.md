# MonitoringSystem
Для работы с данным проектом рассмотрим архитектуру приложения.
Модель у нас одна, однако контроллеров должно быть несколько:

1. KernelAgentLoader - данный контроллер постоянно отслеживает папку 'agents' и линкует динамические библиотеки(модули) из этой папки.
2. NotificationControl - данный контроллер следит за состоянием 
