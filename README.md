# TheOS

**TheOS** is a work-in-progress operating system kernel, currently being developed into a full-fledged OS. It is inspired by Linux, built on the open-source philosophy, and written as a personal journey into understanding how computers *truly* work under the hood.

This project is not about creating the next great operating system. It is about peeling back the abstractions we all take for granted—memory allocation, paging, threading, file systems, userland—and rebuilding them piece by piece until they are no longer mysterious. Every line of code in TheOS represents something I had to struggle with, reason through, and ultimately understand.

At its current stage, TheOS runs in 32-bit protected mode and includes:

* A custom (yet simple) memory allocator with bookkeeping for free/used blocks.
* Paging structures under development.
* Early file structure exploration.
* Basic VGA text mode display.
* Foundations for multi-threading.

Future directions may include moving toward userland support, experimenting with a custom language that targets TheOS directly, and maybe one day porting GCC. But the real aim is not “feature completeness.” The aim is growth—forcing myself to engage with concepts like paging, CPU modes, hardware-level memory management, and the fundamental trade-offs of OS design.

This is a fourth-year Electronics & Communication student’s attempt to learn by doing. Mistakes will happen, and that’s the point. The code is open under the **AGPL** because I believe in the philosophy of shared knowledge: if I struggled to learn this, maybe someone else struggling tomorrow can learn from my stumbles.

TL;DR: TheOS is a playground for learning, an archive of curiosity, and a slow step-by-step effort to demystify the layers that make up modern computing.
