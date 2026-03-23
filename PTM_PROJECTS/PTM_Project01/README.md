\# 🚀 Custom HTTP Server \& Pub/Sub Graph Engine



!\[Java](https://img.shields.io/badge/Java-ED8B00?style=for-the-badge\&logo=java\&logoColor=white)

!\[Multithreading](https://img.shields.io/badge/Multithreading-Enabled-brightgreen?style=for-the-badge)

!\[Design Patterns](https://img.shields.io/badge/Design\_Patterns-OOP-blue?style=for-the-badge)



\## 📖 About The Project



This project is a full-stack, backend framework developed entirely from scratch in Java. It serves as a dual-purpose engine:

1\. A \*\*Multithreaded HTTP Server\*\* capable of parsing raw TCP socket streams, routing requests, and serving dynamic content.

2\. An asynchronous \*\*Computational Graph Engine\*\* based on a Publish-Subscribe (Pub/Sub) architecture, allowing mathematical and logical agents to process data in a highly decoupled manner.



\### 🎯 The Goal

The primary objective of this project was to build a scalable, zero-dependency framework to deeply understand how web servers and message brokers work under the hood. By avoiding high-level frameworks like Spring Boot, this project focuses heavily on \*\*raw socket programming, JVM concurrency, Reflection, and strict adherence to SOLID and OOD Design Patterns.\*\*



\---



\## 🏗️ Architecture Design



The system is divided into two main layers: The Web Layer (Server \& Routing) and the Application Layer (Pub/Sub Engine).



```mermaid

flowchart TD

&#x20;   Client((Client / Browser)) -->|HTTP Request| Server\[HTTP Server Socket]

&#x20;   

&#x20;   subgraph Web Layer

&#x20;       Server -->|Raw Bytes| Parser\[Request Parser]

&#x20;       Parser -->|Parsed URI| Router{Longest Match Router}

&#x20;       Router -->|/api/calc| CalcServ\[Calc Servlet]

&#x20;       Router -->|/api/upload| UpServ\[Upload Servlet]

&#x20;   end



&#x20;   subgraph Computational Graph Engine

&#x20;       CalcServ -->|Inject Data| TM((Topic Manager))

&#x20;       TM -->|Notify| TopicA\[Topic: A]

&#x20;       TM -->|Notify| TopicB\[Topic: B]

&#x20;       TopicA -.->|Trigger Update| Agent1\[Plus Agent]

&#x20;       TopicB -.->|Trigger Update| Agent1

&#x20;       Agent1 -->|Publish Result| TopicC\[Topic: C]

&#x20;   end

