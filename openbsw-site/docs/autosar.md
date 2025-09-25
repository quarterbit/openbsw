# AUTOSAR Integration

As an add-on to OpenBSW, we provide the models to make it **AUTOSAR ICC1 compliant**.

## Why Should This Interest You?

**OpenBSW allows you to reuse AUTOSAR SWCs and dive into modern MCU development without going greenfield.**

### Key Benefits

- **🔄 Reuse Existing Assets:** Keep your AUTOSAR Software Components (SWCs) while modernizing the underlying stack
- **🚀 Modern Development:** Code-first approach with textual models instead of complex GUI tools
- **⚡ Faster Iterations:** No tooling bottleneck - use VS Code, Git, and standard CI/CD pipelines
- **🎯 Best of Both Worlds:** AUTOSAR compatibility on top with flexible C++ basic software below

---

## The AUTOSAR Challenge

### A Complex Standard
The AUTOSAR standard contains a very large number of features with significant complexity:
- **Redundant Features:** The same functionality can be achieved in different ways, making maintenance difficult
- **Rigid Specification:** The entire software stack is specified in detail, making extension challenging  
- **Model-Heavy Approach:** Heavily based on modeling and code generation, creating usability barriers

### Consequences of Complexity
- **High Learning Curve:** Every developer needs at least basic AUTOSAR knowledge
- **Implementation Challenges:** Tool vendors struggle to keep up with feature evolution
- **Development Bottlenecks:** Most tools don't support modern CI/CD practices, leading to long update cycles

### The Tooling Bottleneck
- **Limited Access:** Model changes require specialized tools not available to all developers
- **Advanced Skills Required:** Complex tooling demands significant expertise
- **Version Control Issues:** Models can't be easily merged with standard VCS tools
- **Slow Change Cycles:** Every modification requires a tooling detour

---

## The ESR AUTOSAR Stack Approach

### Smart Simplification
- **Essential Feature Subset:** Implements features sufficient for all typical automotive projects
- **ICC1 Compliance:** 100% AUTOSAR compatible at the application interface layer
- **Modern Foundation:** Flexible and open C++ stack below the AUTOSAR interface

### Code-First Philosophy
- **Configuration as Code:** Part of configuration expressed directly in code
- **Sensible Defaults:** Remaining configuration simplified through intelligent defaults
- **Textual Models:** Models treated like code for better tooling integration

---

## Technical Capabilities

### 100% AUTOSAR Compatible (ICC1)
Built on flexible C++ Basic Software with full interface compliance:

### Textual Modeling Support
- **Application Level Stack Configuration**
- **AUTOSAR Software Components (SWCs):** Interfaces, connections, signal mapping
- **Vehicle Bus Configuration:** CAN, LIN, Ethernet setup
- **Protocol Configuration:** RTE, COM, DCM, DEM, NVM
- **ARXML Import/Export:** Seamless integration with existing toolchains

### ESR "Automate" Tool
Advanced textual AUTOSAR authoring capabilities:
- **Large Model Support:** Handles very large models and any valid AUTOSAR XML
- **Command Line Based:** Integrates with code editors (VS Code) and supports user-defined macros
- **Free Online Demo:** Try before you implement

### Development Tools Integration

#### Automate VS Code Plugin
- **Syntax Highlighting:** Clear visual code structure
- **Auto Completion:** Faster model authoring
- **Error Annotation:** Problems indicated early in development
- **Reference Navigation:** Efficient navigation through large models

#### autosar-py Python Integration
- **Simple Installation:** Single Python wheel (`pip install`)
- **Programmatic Access:** Read and write ARXML from Python
- **Model Manipulation:** Build, analyze, and edit models programmatically
- **IDE Support:** Intellisense in Python IDEs (PyCharm, VS Code)
- **Scalability:** Supports very large models and any valid AUTOSAR XML

---

## Getting Started with AUTOSAR on OpenBSW

1. **Evaluate Your Current AUTOSAR Assets** - identify SWCs and configurations to migrate
2. **Try the Automate Tool** - use our free online demo to explore textual modeling
3. **Plan Your Migration** - gradual transition from traditional AUTOSAR toolchain
4. **Leverage Modern Practices** - integrate with Git, CI/CD, and team development workflows

---

## Get in Contact

Ready to explore AUTOSAR integration with OpenBSW? **Drop us an email:**

<div align="center">
<img src="images/email-qr-thomas.png" alt="Email QR Code" width="150"/>

</div>

We're here to help you modernize your AUTOSAR development while protecting your existing investments.

---

**Ready to modernize your AUTOSAR development while protecting your investments?** The ESR AUTOSAR stack brings the power of OpenBSW's modern architecture to your existing AUTOSAR projects.