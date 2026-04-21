# 🤖 Iterated N Prisoner's Dilemma Tournament

Welcome to the **N Prisoner's Dilemma Tournament**. This Project is *ultimate logic battlefield* where you can test your skills to win the Tournament. Unlike the classic 2-player version, here you are face to face with a crowd. Your success depends not just on one opponent, but on the collective behavior of the entire group. Rule the crowd or be a sheep in the herd, it's your choice.

> "The flesh is weak, but the logic is iron." — *Ferruscpp*

---
## Note for non-C++ developers:
> Even if you are not familiar with C++, the core logic of the tournament is based on simple mathematical strategies. You can describe your algorithm in the Discussions section, and someone from the community (or the maintainer) can help translate it into code!

## ⚔️ The Concept
The tournament is not a duel. It's a social simulation. In each round, **N participants** decide simultaneously: **Cooperate** or **Defect**. The charm of **Defection** is so strong but you will pay for it in the future. The flaws of **Cooperation** are obvious: *fears will they **Cooperate** too? or not?*. But the advantages is good ideas of everyone's cooperation.

The payoff depends on the total number of cooperators:
* **The Individual's Temptation:** You might get a better result by defecting, but if *everyone* defects, everyone suffers.
* **The Group's Survival:** Maximum collective benefit is reached only if the whole group stays loyal.
* **The Betrayal:** Can you trust N-1 people at the same time?

> "No world shall be beyond my rule; no enemy shall be beyond my wrath." - *Emperor of the mankind*
---
or
> "There is a fire burning within each of us. We must use its warmth to protect, and its rage to destroy the enemies of humanity." - *Vulkan He'stan*
---

## 🚀 How to Participate
Think your algorithm can outsmart a crowd?
1. **Fork** this repository.
2. **Create** your strategy in the `strategies/` directory.
3. **Implement** your logic: your bot receives the history of actions and score from **all** N participants.
4. **Private Submission:** To keep your logic secret, do not use Pull Requests. Send your code to ferrus.manus.cpp@proton.me to enter the next slaughter.

## 🛠 Project Structure
- `/src` — The core engine (managing N-player rounds and scoring).
- `/strategies` — The armory (all participant bots).
- `.github/workflows` — Automated CI/CD build tests.

## 🏗 Build & Run
To compile the tournament engine locally:
```bash
g++ src/*.cpp strategies/*.cpp -o tournament
./tournament
```

## 📜 Tournament Rules
Check out the **detailed rules [here](https://github.com/Ferruscpp/Ndilemma/wiki/Rules#tournament-rules)**.
* **Rounds:** 1,000 to 10,000 (randomized to prevent "last-move" exploits).
* **Goal:** Minimize your total prison years.
* **Format:** All-vs-All or Group Stages.
