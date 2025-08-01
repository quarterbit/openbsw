// Copyright 2024 Accenture.

#pragma once

#include <console/IConsoleCommand.h>
#include <platform/estdint.h>

namespace demo
{
namespace console
{

/**
 * Console command for Ethernet demo functionality.
 * 
 * Provides commands to:
 * - Check Ethernet status
 * - Display network statistics
 * - Test basic Ethernet communication
 */
class EthernetDemoCommand : public ::console::IConsoleCommand
{
public:
    // IConsoleCommand interface
    char const* getName() const override;
    char const* getDescription() const override;
    void execute(
        ::util::stream::ISharedOutputStream& outputStream,
        uint8_t argc,
        char const* const argv[]) override;

private:
    void showStatus(::util::stream::ISharedOutputStream& outputStream);
    void showStatistics(::util::stream::ISharedOutputStream& outputStream);
    void testSend(::util::stream::ISharedOutputStream& outputStream);
    void showHelp(::util::stream::ISharedOutputStream& outputStream);
};

} // namespace console
} // namespace demo