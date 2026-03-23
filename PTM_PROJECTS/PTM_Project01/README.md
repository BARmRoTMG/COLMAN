# 🚀 Custom HTTP Server & Pub/Sub Graph Engine

![Java](https://img.shields.io/badge/Java-ED8B00?style=for-the-badge&logo=java&logoColor=white)
![Multithreading](https://img.shields.io/badge/Multithreading-Enabled-brightgreen?style=for-the-badge)
![Design Patterns](https://img.shields.io/badge/Design_Patterns-OOP-blue?style=for-the-badge)

## 📖 About The Project

This project is a backend framework developed entirely from scratch in Java. It serves as a dual-purpose engine:

1. A **Multithreaded HTTP Server** capable of parsing raw TCP socket streams, routing requests, and serving dynamic content.
2. An asynchronous **Computational Graph Engine** based on a Publish-Subscribe (Pub/Sub) architecture, allowing mathematical and logical agents to process data in a highly decoupled manner.

### 🎯 The Goal
The primary objective of this project was to build a scalable, zero-dependency framework to deeply understand how web servers and message brokers work under the hood. By avoiding high-level frameworks like Spring Boot, this project focuses heavily on **raw socket programming, JVM concurrency, Reflection, and strict adherence to SOLID and OOD Design Patterns.**

---

## 🏗️ Architecture Design

The system is divided into two main layers: The Web Layer (Server & Routing) and the Application Layer (Pub/Sub Engine).

```mermaid
flowchart TD
    Client((Client / Browser)) -->|HTTP Request| Server[HTTP Server Socket]
    
    subgraph Web Layer
        Server -->|Raw Bytes| Parser[Request Parser]
        Parser -->|Parsed URI| Router{Longest Match Router}
        Router -->|/api/calc| CalcServ[Calc Servlet]
        Router -->|/api/upload| UpServ[Upload Servlet]
    end

    subgraph Computational Graph Engine
        CalcServ -->|Inject Data| TM((Topic Manager))
        TM -->|Notify| TopicA[Topic: A]
        TM -->|Notify| TopicB[Topic: B]
        TopicA -.->|Trigger Update| Agent1[Plus Agent]
        TopicB -.->|Trigger Update| Agent1
        Agent1 -->|Publish Result| TopicC[Topic: C]
    end

---

## 🛠️ UML & Design Patterns

The project heavily utilizes Design Patterns to ensure maintainability and low coupling. Below is a simplified class diagram highlighting the core patterns used:

classDiagram
    class TopicManager {
        - static instance: TopicManager
        - topics: ConcurrentHashMap
        + getInstance() TopicManager
        + getTopic(name) Topic
    }
    <<Singleton>> TopicManager

    class Topic {
        - subs: List~Agent~
        + subscribe(Agent)
        + publish(Message)
        + notifyAgents()
    }
    <<Observable>> Topic

    class Agent {
        <<Interface>>
        + update()
    }
    <<Observer>> Agent

    class PlusAgent {
        + update()
    }
    
    class ParallelAgent {
        - wrappedAgent: Agent
        + update()
    }
    <<Decorator>> ParallelAgent

    class Servlet {
        <<Interface>>
        + handle(RequestInfo, OutputStream)
    }
    <<Strategy>> Servlet

    TopicManager --> Topic : Manages
    Topic --> Agent : Notifies
    Agent <|.. PlusAgent : Implements
    Agent <|.. ParallelAgent : Implements
    ParallelAgent o-- Agent : Wraps