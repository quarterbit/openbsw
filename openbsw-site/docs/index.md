



# Eclipse OpenBSW

<div align="center">
<img src="https://eclipse.dev/openbsw/openbsw_logo.svg" alt="OpenBSW Logo" width="120"/>
</div>

## Accelerate R&D for automotive MCUs. Leverage OSS collaboration & innovation. Reduce vendor lock-in.

Eclipse OpenBSW is a code-first, open source software platform for automotive microcontrollers, built from 15+ years of SOP project experience. Already on the road in millions of cars with premium and volume carmakers, OpenBSW powers central and zonal SDV architectures. 

**Why Code-First?** Traditional automotive software development relies heavily on GUI-based modeling tools that create obstacles to modern development practices like continuous integration. OpenBSW takes a different approach: plain code is sufficient for most tasks, and when code generation is needed, we use textual languages instead of GUI tools.

### OpenBSW in a Nutshell

- <img src="images/chip-mcu.png" width="24" style="display: inline; vertical-align: middle;"> **Microcontroller Focus:** Tailored for automotive microcontrollers, not general-purpose computing platforms
- <img src="images/power-lowpower.png" width="24" style="display: inline; vertical-align: middle;"> **Resource Efficient:** Optimized for memory and processing constraints typical in automotive ECUs
- <img src="images/shield-safety.png" width="24" style="display: inline; vertical-align: middle;"> **Safety Integration:** Designed with automotive safety standards as a core requirement, not an afterthought
- <img src="images/code-config.png" width="24" style="display: inline; vertical-align: middle;"> **Development Experience:** Modern tooling and practices adapted for the automotive domain

Our engineers contribute upstream and apply production-grade practices—so you can move faster with less vendor lock-in.

---

## What it does

Eclipse OpenBSW brings modularity to automotive microcontroller software, enabling developers to explore new ideas and innovate more freely. Unlike rigid "one size fits all" solutions, OpenBSW offers a customizable stack that scales from very small to very large microcontroller projects.

**Modern Development Experience:** Built with C++ and designed for Rust support, OpenBSW enables the use of well-established programming tools like VS Code, Git, and typical CI/CD pipelines. This brings automotive software development in line with modern software engineering practices.

**Real-World Impact:** With configuration-as-code, code generation from textual models, and support for modern workflows, OpenBSW helps you unlock the full potential of your MCU projects while attracting talent from the broader software development community.

---

## Key Features

- <img src="images/code-config.png" width="24" style="display: inline; vertical-align: middle;"> **Code-First Approach:** Plain code for most tasks, textual languages for code generation instead of GUI-based tools.
- <img src="images/cpp.png" width="24" style="display: inline; vertical-align: middle;"> <img src="images/rust.png" width="24" style="display: inline; vertical-align: middle;"> **Modern Languages:** C++ implementation with planned Rust support for next-generation development.
- <img src="images/flow-ci.png" width="24" style="display: inline; vertical-align: middle;"> **Developer-Friendly:** Use VS Code, Git, and standard CI/CD pipelines—no specialized automotive tools required.
- <img src="images/puzzle-modular.png" width="24" style="display: inline; vertical-align: middle;"> **Scalable Architecture:** Customizable stack that scales from small to large ECU projects.
- <img src="images/shield-safety.png" width="24" style="display: inline; vertical-align: middle;"> **Safety-Ready:** Built-in "safety shell" approach for ISO26262 functional safety compliance.
- <img src="images/clock-realtime.png" width="24" style="display: inline; vertical-align: middle;"> **Real-Time Capable:** Cyclic execution models and real-time requirements for safety-critical systems.
- <img src="images/zephyr.png" width="24" style="display: inline; vertical-align: middle;"> **RTOS Flexibility:** On the road with FreeRTOS; Zephyr RTOS support enables 800+ MCUs.

---

## Market Context & Development Challenges

Developers face several challenges in automotive MCU projects:

- Integration is slow and labor-intensive, causing long round-trip times for changes.
- Complexity of models in complex GUI tools is difficult to manage.
- Strict architecture restrictions limit flexible exploitation of MCU capabilities.
- Modern code workflows like compare, merge, management, and code-review are hard to apply on modeling.

These issues slow down development and complicate project workflows. OpenBSW addresses these with innovative solutions:

- **Configuration as code** ("Terraform the SDV")
- **Code generation from textual models**
- **Modern CI/CD integration**

---

## Future Directions

1. **Enabling New BSW Collaboration:** Foster new ways of collaboration in Basic Software (BSW) development.
2. **Scaling SOP-Proven Software:** Scale software proven in SOP to larger, more complex systems.
3. **Legacy SWC Flexibility:** Run legacy software components with or without AUTOSAR constraints.
4. **AI-Driven Development:** Develop AI for automotive in Visual Studio Code, leveraging modern tools.

---

## OpenBSW in a nutshell

OpenBSW is a modular, production-proven basic software stack for automotive MCUs. It enables:

- Fast, reliable integration of embedded software components
- Real-time, deterministic operation across platforms
- Modern development workflows (CI/CD, configuration as code)
- Support for both AUTOSAR and non-AUTOSAR projects
- Proven on the road in millions of vehicles

---

### Sweet-Spot ECUs for OpenBSW

- <img src="images/chip-mcu.png" width="24" style="display: inline; vertical-align: middle;"> **Body & Gateway ECUs with high integration**
- <img src="images/chip-mcu.png" width="24" style="display: inline; vertical-align: middle;"> **Peripheral control ECUs** (Door, Seat, Trunk, …)
- <img src="images/chip-mcu.png" width="24" style="display: inline; vertical-align: middle;"> **Zone ECUs with Ethernet/CAN**
- <img src="images/chip-mcu.png" width="24" style="display: inline; vertical-align: middle;"> **MCU domain in HPCs** (e.g., ADAS & Infotainment)

---

## The Power of Eclipse OpenBSW

- Shipped in millions of cars already
- Zephyr RTOS supports 800+ devices
- Eclipse ThreadX for functional safety is coming 

---

## Main Contributors

<img src="https://upload.wikimedia.org/wikipedia/commons/3/3d/Accenture.svg" alt="Accenture Logo" width="120"/>

OpenBSW is developed with major contributions from **Accenture** and the open-source community, under the governance of the Eclipse Foundation.

---

## Get Involved

- [GitHub Repository](https://github.com/eclipse-openbsw/openbsw)
- [Eclipse Project Proposal](https://projects.eclipse.org/proposals/eclipse-openbsw)
- [Join the Community](https://eclipse.dev/sdv/)

---

OpenBSW is part of the Eclipse SDV ecosystem. For more information, visit the [Eclipse SDV website](https://eclipse.dev/sdv/).
