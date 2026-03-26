## Project Context
- Description: this is a research project into capabilities of automated coding agents applied to problems in computational mathematics / rigorous numerical methods / computer assisted proofs in dynamics.
- Primary Language: C++20
- Tools: CMake, make, lcov, ctest, gnuplot
- Libs: [CAPD](https://github.com/CAPDGroup/CAPD)
- System requirements: libgmp-dev libmpfr-dev libboost-all-dev git cmake autoconf libtool


## Dependencies & Environment

- use ``apt-get`` to manage dependencies if needed. Create or update a file ``requirements.sh`` that contain all ``apt-get`` commands to install neccessary packages. 
- use the git repository ``https://github.com/CAPDGroup/CAPD`` as a submodule in this project. Use build instructions from ``https://github.com/CAPDGroup/CAPD/blob/master/README.md`` to build CAPD with cmake. Install all dependencies needed by CAPD using apt-get.
- install ``libgmp-dev libmpfr-dev libboost-all-dev git cmake autoconf libtool`` as they are required by CAPD.
- Use ``CMake`` building system to configure build procedure for this project. 
- Install any dependencies (other than ``CAPD`` library and those that can be installed with `apt-get`) in ``${HOME}/deps`` folder, when needed (e.g. the ``lcov`` tool in a different version than standard).


## Workflow instructions

ALWAYS Follow the following list of Workflow instructions TO THE LETTER:

- The names of the branches you create for all tasks should begin with jules, e.g. `jules/develop-some-feature`, `jules/research-some-task`.
- ALWAYS work in ``./build/`` folder outside of the main directory ``./``. At all cost KEEP THE REPO CLEAN of the build artifacts!
- There might be different `*_main` files in the `./src` directory, that are supposed to be compiled separatley into binaries. If you are creating new program with main, put it into `{name}_main.cpp` file, where {name} is a suitable short identifier based on the feature or research you are doing.
- Keep separate files for declarations (`.h`) in `./include/` and implementation (`.cpp`) in `./src/`.
- If you are using any commands to build something for a specific task (e.g. when reserching a task, looking for a bug, etc.), prepare a ``jules-build-{my-build-task}.sh`` command in the main directory, so that I can re-run your setup in my local repository. The name ``{my-build-task}`` should be short but descriptive, e.g. ``finding-fix-points``, ``bug-in-integration``. 
- You might use scientific materials stored in ``literature`` folder to search for concepts and algorithms that might be helpful in implementing tasks. You might also search internet for required additional sources. 
- When implementing mathematical concepts and/or algorithms, write descriptive comments explaining what the algorithm do and what is the mathematical concept behind them. If you are using something from the literature sources or from the Internet, please add relevant citation somewhere in the comments.

END of Workflow instructions.


## Coding Standards & Style

ALWAYS Follow the following list to the letter when doing any tasks:

- Datastructures names should be CamelCase, method/function names should use underscore_case. Constants should be UPPER_UNDERSCORE_CASE. 
- All components must be designed to be testable in isolation. Dependency injection (via templates) should be used to mock dependencies.
- All public interfaces must be documented with Doxygen-style comments. Explain the mathematical concept being represented, not just the code implementation.
- Use exceptions for errors (e.g., domain errors, convergence failures). Provide descriptive error messages,  allowing to locate where they are thrown based on the information in the what() string. Always provide "ClassName::method_name(): " in the message!
- Avoid hardcoded constants (like epsilon) inside generic algorithms; provide them as configuration parameters or traits of the scalar type.
- Avoid `using namespace std;` in header files.

END of Coding Standards & Style.


## Development Protocol

YOU MUST follow the following list if you are a DEVELOPER:

- The name of the branch you create MUST begin with `jules/develop`, e.g. `jules/develop-some-feature`.
- Read ``DEVLOG.md`` if it exists to learn about current state of the project.
- In a single session, read the first FEATURE in ``FEATURES.md`` marked as ``NEW`` or ``UNFINISHED``
- Implement task defined in the FEATURE following all the guidelines above and the Testing Protocol described below.
- If all the tests passes and the code coverage is >= 80% then mark the FEATURE in ``FEATURES.md`` as ``DONE``.
- Otherwise mark the FEATURE in ``FEATURES.md`` as ``UNFINISHED`` and update ``DEVLOG.md`` with information on any bug or difficulty you have encoutered when developing a FEATURE.

END of Development Protocol.


## Testing Protocol

YOU MUST follow the following list if you are a DEVELOPER or a TESTER:

- EVERY new feature or bug fix MUST include a corresponding unit test in the `tests/` directory.
- ALWAYS prepare unit tests using Boost.Test framework. Use pre-compiled version.
- You should try to achive the code coverage >= 80%. Use ``lcov`` tool for code coverage tests.
- Unit tests must cover edge cases and verify the mathematical correctness of operations (e.g., derivative of a polynomial).

END of Testing Protocol.


## Research Protocol

YOU MUST Follow the following list if you are a RESEARCHER:

- The name of the branch you create MUST begin with `jules/research`, e.g. `jules/research-some-feature`.
- Read ``MATHEMATICS.md`` and ``RESEARCH_LOG.md`` if they exists to learn about current state of the research.
- In a single session read the first research TASK specified in `jules/RESEARCH.md` that is marked as `NEW` or `UNFINISHED`. 
- If the TASK in NEW, then clear the file ``RESEARCH_LOG.md`` completely, to start anew. Otherwise use ``RESEARCH_LOG.md`` to check the progress of the UNFINISHED TASK.
- The TASK is a general description followed by a list of SUBTASKS. 
- Some SUBTASKS can be DONE. You can use this to guide your next steps. You are free to mark the SUBTASKS as DONE or UNFINISHED as your work progress. 
- do RESEARCH in iterations, after the iteration write a subsection called ``ITERATION {n}``, where {n} is the next number for the item in the file ``RESEARCH_LOG.md``.
- Create or update a plan for the research TASK in ``RESEARCH_GOAL.md`` of what it means to be MATHEMATICALLY PLAUSIBLE and the criterion of the TASK to be SUCCESS.
- re-read `jules/MATHEMATICS.md`, understand it, re-write it if necessary with the mathematics concepts needed for this TASK.
- The TASK is FAILING if it does not meet the definition of MATHEMATICALLY PLAUSIBLE and is not a SUCCESS. 
- If the TASK keeps FAILING, YOU MUST DO AT LEAST 10 iterations before you give up. If you give up, commit all the changes and create PR for me to review the current state of the TASK.
- If the TASK meets the criterion of MATHEMATICALLY PLAUSIBLE and is a SUCCESS, mark the TASK as DONE in `jules/RESEARCH.md`, commit changes and create PR for me.

END of Research Protocol.