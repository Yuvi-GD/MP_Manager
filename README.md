# MP Manager

MP Manager is a modular session orchestration and lobby management framework for Unreal Engine. Handling asynchronous multiplayer handshakes requires strict state management to avoid race conditions and session desynchronization. This plugin is engineered to abstract the complexities of the Online Subsystem (OSS) while maintaining server authority over the lobby lifecycle.

**Important Note on Session Networking:**
MP_Manager provides the abstraction layer, state machine, and UI orchestration. It does **not** natively execute the network handshakes for creating, finding, or leaving sessions out of the box. Those operations require an active Online Subsystem (OSS) such as Steam, Epic Online Services (EOS), or EIK. By acting as a standardized wrapper, the plugin allows you to seamlessly hot-swap backend providers without rewriting your underlying game mode logic.

## Core Features

### Session Orchestration
* Wrapper functions to create, find, join, and leave multiplayer sessions via your chosen OSS
* Real-time session state machine updates
* Modular level and game mode selection

### Player Management
* Dynamic player list tracking and synchronization
* Secure Remote Procedure Calls (RPCs) for player kicking functionality
* Synchronized character selection and metadata updates within the pre-match lobby
* Player name configuration

### Lobby and UI Integration
* Decoupled UI architecture utilizing low-level event dispatchers
* Integrated multiplayer chat system
* Basic settings panel
* Demo gameplay environment for testing

## Technical Architecture

The framework utilizes a component-based architecture designed to strictly separate heavy backend networking from the user interface flow:

* **OSS Abstraction Layer**: A generalized interface wrapper standardizes calls to diverse backend providers. This allows developers to transition smoothly between local network testing and production environments like Steam or EOS.
* **Asynchronous State Machine**: A strict state machine tied to the GameMode processes OSS handshakes sequentially. This prevents race conditions during rapid join/leave events and preserves memory integrity across client connections.
* **Event-Driven Synchronization**: Real-time player metadata (such as selected characters or readiness) is broadcast via multicast delegates directly to the UI, ensuring the visual state remains perfectly synchronized with the server's authoritative memory.

## Integration Guide

To successfully implement MP_Manager into your environment, follow these standard steps:

1. **Install an Online Subsystem**: Install and configure your preferred OSS plugin (e.g., EIK Plugin by Betide Studio).
2. **Add the Plugin**: Place the MP_Manager plugin into your project's `Plugins` directory and enable it in the editor.
3. **Configure the GameMode**: Integrate the lobby settings and state machine within your active GameMode.
4. **Implement Interfaces**: Ensure your Player Controllers implement the required interfaces to handle session callbacks properly.
5. **Set Up the UI**: Bind your UMG frontend widgets to the exposed C++ event dispatchers for lobby tracking and character selection.


## Contributing

We welcome community contributions. Feel free to submit pull requests or [open issues](https://github.com/Yuvi-GD/MP_Manager/issues) to discuss potential improvements or report bugs.

## License

This project is licensed under the GNU General Public License v3.0. Please see the [LICENSE](LICENSE) file for more details.
