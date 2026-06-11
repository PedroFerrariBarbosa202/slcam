<h1 align="center">
    SLCAM DOCUMENTATION
    <br>
</h1>

<h4 align="center">Documentation of the SLCam Payload.</h4>

<p align="center">
    <a href="https://github.com/spacelab-ufsc/spacelab#versioning">
        <img src="https://img.shields.io/badge/status-in%20development-red?style=for-the-badge">
    </a>
    <a href="https://github.com/spacelab-ufsc/slcam/releases">
        <img alt="GitHub release (latest by date)" src="https://img.shields.io/github/v/release/spacelab-ufsc/slcam?style=for-the-badge">
    </a>
    <a href="https://github.com/spacelab-ufsc/slcam/releases">
        <img alt="GitHub commits since latest release (by date) for a branch" src="https://img.shields.io/github/commits-since/spacelab-ufsc/slcam/latest/documentation?style=for-the-badge">
    </a>
    <a href="https://github.com/spacelab-ufsc/slcam/commits/master">
        <img alt="GitHub last commit (branch)" src="https://img.shields.io/github/last-commit/spacelab-ufsc/slcam/documentation?style=for-the-badge">
    </a>
    <a href="https://github.com/spacelab-ufsc/slcam/issues">
        <img alt="GitHub issues by-label" src="https://img.shields.io/github/issues/spacelab-ufsc/slcam/documentation?style=for-the-badge">
    </a>
    <a href="">
        <img src="https://img.shields.io/badge/DOC%20tool-LaTeX-yellow?style=for-the-badge">
    </a>
    <a href="https://github.com/spacelab-ufsc/slcam/actions">
        <img src="https://img.shields.io/github/workflow/status/spacelab-ufsc/slcam/Build%20LaTeX%20documentation?style=for-the-badge">
    </a>
</p>

<p align="center">
    <a href="#overview">Overview</a> •
    <a href="#dependencies">Dependencies</a> •
    <a href="#building">Building</a> •
    <a href="#license">License</a>
</p>

## Overview

> TODO

## Dependencies

The following dependencies are required for building this project:

* [sphinx-rtd-theme](https://pypi.org/project/sphinx-rtd-theme/)
* [sphinxcontrib-bibtex](https://pypi.org/project/sphinxcontrib-bibtex/)
* [sphinx-subfigure](https://pypi.org/project/sphinx-subfigure/)

## Building

After installing the required dependencies, just execute the following command:

```
make html
```

### Generating the PDF file

```
make latexpdf
```

## License

This documentation is licensed under Creative Commons BY-SA 4.0 license.
