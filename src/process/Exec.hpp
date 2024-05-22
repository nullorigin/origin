#pragma once

#ifndef EXEC_HPP
#define EXEC_HPP
#include "Basic.hpp"
#include "Message.hpp"
#include "Timer.hpp"
#include <string>
namespace origin {
class Run {
private:
  f128 Time_out_max = 0;
  f128 Time_in_max = 0;
  u32 Min_args = 0;
  std::string Output;
  std::string Input;
  Timer Timers[2] = {Timer(), Timer()};
  i32 Run_state{};
  Code Run_status{};
  u64 Cycles{};
  u64 Max_cycles{};
  std::string Timer_text = " ";
  std::string Exec_text = " ";

public:
  static const i32 UNINITIALIZED = 0, INITIALIZING = 1, INITIALIZED = 2,
                   STARTING = 3, STARTED = 4, PAUSING = 5, PAUSED = 6,
                   RESUMING = 7, RESUMED = 8, STOPPING = 9, STOPPED = 10,
                   RESTARTING = 11, RESTARTED = 12, EXITING = 13, EXITED = 14,
                   KILLING = 15, KILLED = 16;
  static const std::string RUN_STATES[17];
  static const i32 RUN_MAP[17][8];

  static const std::string CMD[16];
  static const u32 CMD_LEN[16];
  static const u32 CMD_MAP[16];
  static const std::string CMD_ARG[16];
  static const i32 ALL_TXT = -1, PROMPT_TXT = 0, STATE_TXT = 1, CYCLE_TXT = 2,
                   TIMER_TXT = 3, EXEC_TXT = 4;
  explicit Run(const i8 *cmd) { parse(cmd); }
  explicit Run(const std::string &cmd) { parse(cmd); }
  Run(i8p cmd, i8p argv[]) { exec(cmd, argv); }
  /* A dependency map of applicable run states to enter into after a state
switch. Uses the constants above as specifiers for the equivalent index. */

  Run();
  Run(i32 /*argc*/, i8 ** /*argv*/);
  ~Run() = default;

  // The main loop of the application. Splits the output into a separate thread
  // and continues updating the input status until the application is exited or
  // a time limit is reached.
  auto loop(f128 runtime = 0) -> Code;
  // Sets the run state of the application to 'Initializing' and Upon success,
  // sets the run state to 'Initialized'.
  auto doInit() -> Code;
  // Sets the run state of the application to 'Starting' and executes specified
  // commands. Upon success,the run state is set to 'Started'.
  auto doStart() -> Code;
  // Sets the run state of the application to 'Pausing' and executes specified
  // commands. Upon success, the run state is set to 'Paused'. In addition, the
  // output is frozen and saved until the 'resume' command is executed, at which
  // point it continues from where it left off.
  auto doPause() -> Code;
  // Sets the run state of the application to 'Resuming' and executes specified
  // commands. Upon success, the run state is set to 'Resumed'. This command is
  // only valid if the application is in the 'Paused' state. In addition, the
  // output is frozen until this command is called at which point it
  // continues from where it left off.
  auto doResume() -> Code;
  // Sets the run state of the application to 'Stopping' and executes specified
  // commands. Upon success, the run state is set to 'Stopped'. In this state
  // The only applicable commands are 'start', 'restart' and 'exit'.
  auto doStop() -> Code;
  // Sets the run state of the application to 'Restarting' and executes
  // specified commands. Upon success, the run state is set to 'Restarted'. All
  // Variables are reset to their initial values.
  auto doRestart() -> Code;
  // Sets the run state of the application to 'Exiting' and executes specified
  // commands. Upon failure, the kill command is executed and forces the
  // application to close. Upon success, the run state is set to 'Exited' and
  // exits normally.
  auto doExit() -> Code;
  // Sets the run state of the application to 'Killing' and then 'Killed'. The
  // application is forced to close when this command is executed.
  auto doKill() -> Code;

  // Returns the entire map of valid run states to enter into during a state
  // switch.
  static inline auto getRunMap() -> const i32 (*)[8] { return RUN_MAP; }
  // Returns an array of applicable run states in which to switch to
  // from a given previous state.
  static inline auto getStateNext(i32 rstate) -> const i32 (*)[8] {
    return &RUN_MAP[rstate];
  }
  // Returns the std::string representation of a given run state.
  static inline auto getStateString(i32 rstate) -> std::string {
    return RUN_STATES[rstate];
  }
  auto getArg(const std::string &command) -> std::string;
  auto getCmd(const std::string &command) -> u32;
  // Returns the std::string representation of a given command from its index.
  static inline auto getCmd(u32 index) -> i32 { return CMD_MAP[index]; }
  // Determines if the application is in a state in which it is actually
  // running.
  auto isRunning() const -> Code;
  // Returns true if the application is in the specified state.
  inline auto isState(const i32 rstate) const -> Code {
    return Run_state == rstate ? Code::True : Code::False;
  }
  inline auto getRunState() const -> i32 { return Run_state; }
  auto setOutput(const std::string &output, bool format = false) -> Code;
  inline auto getOutput() -> std::string { return Output; }
  auto setInput(const std::string &in, bool format = false) -> Code;
  inline auto getInput() const -> std::string { return Input; }
  inline auto getCycles() const -> u64 { return Cycles; }
  inline auto setCycles(u64 cycles) -> void { Cycles = cycles; }
  auto incrementCycles() -> Code;
  inline auto getMaxCycles() const -> u64 { return Max_cycles; }
  auto setMaxCycles(u64 cycles = 0) -> Code;
  inline auto resetCycles() -> void { Cycles = 0; }
  inline auto setRunStatus(Code rstatus) -> Code {
    return Run_status = rstatus;
  }
  inline auto getRunStatus() const -> Code { return Run_status; }
  auto setRunState(i32 target) -> Code;
  auto processCycles() -> Code;
  auto processState(i32 rstate) -> Code;
  // Reads input and writes output from various sources and to destinations,
  // with actions similar to a shell.
  auto processOut() -> Code;
  auto processIn() -> Code;
  auto processIO() -> Code;
  auto setMinArgs(u32 min_args) -> Code;
  auto getMinArgs() -> u32;

  static auto call(const std::string &cmd) -> std::string;

  static auto call(i8p cmd) -> std::string;
  auto exec(i8p command, const i8p argv[]) -> Code;
  auto parse(const std::string &cmd) const -> std::string;
  auto getText(i32 name, const std::string &dlim = "\n") -> std::string;
};
} // namespace origin
#endif