# Contributing to Operating Systems OER

These are recommendations when contributing to the contents of the Operating Systems OER repository.
They consider contributions to both actual content (mostly Markdown) and support code (demo, lab activities) made via Git.

## First Steps

Some good first steps and best practices when using Git are explained here:

* the Git Immersion tutorial: <https://gitimmersion.com/>
* the Atlassian tutorial: <https://www.atlassian.com/git/tutorials/learn-git-with-bitbucket-cloud>
* this blog post on the ROSEdu Techblog: <https://techblog.rosedu.org/git-good-practices.html>

## Language

All of our content is developed in English.
This means we use English for content, support code, commit messages, pull requests, issues, comments, everything.

## Content Writing Style

This section addresses the development of session content and other Markdown files.

Write each sentence on a new line.
This way, changing one sentence only affects one line in the source code.

Use the **first person plural** when writing documentation and tutorials.
Use phrases like "we run the command / app", "we look at the source code", "we find the flag".

Use the second person for challenges and other individual activities.
Use phrases like "find the flag", "run this command", "download the tool".

## Images

Images and diagrams would ideally be animated on slides.
Aim to use `reveal.js` features to animate drawing of diagrams.

If `reveal.js` drawing is difficult, use [draw.io](https://app.diagrams.net/) to create diagrams.
Ideally you would "animate" those diagrams by creating multiple incremental versions of the diagram and adding each to a slide;
when browsing slides pieces of these diagrams will "appear" and complete the final image, rendering an animation-like effect.

For text where no animation is required, use diagrams / images created with [draw.io](https://app.diagrams.net/).
If using external images / diagram, make sure they use a CC BY-SA license and give credits (mention author and / or add link to the image source).

## Issues

When opening an issue, please clearly state the problem.
Make sure it's reproducible.
Add images if required.
Also, if relevant, detail the environment you used (OS, software versions).
Ideally, if the issue is something you could fix, open a pull request with the fix.

## Discussions

Use GitHub discussions for bringing up ideas on content, new chapters, new sections.
Provide support to others asking questions and take part in suggestions brought by others.
Please be civil when taking part in discussions.

## Pull Requests

For pull requests, please follow the [GitHub flow](https://docs.github.com/en/github/collaborating-with-pull-requests/proposing-changes-to-your-work-with-pull-requests/creating-a-pull-request-from-a-fork): create a fork of the repository, create your own branch, do commits, push changes to your branch, do a pull request (PR).
The destination branch of pull requests is the default `master` branch.

Make sure each commit corresponds to **one** code / content change only.
If there are multiple commits belonging to a given change, please squash the commits.

Also make sure one pull request covers only **one** topic.

Use commit messages with verbs at imperative mood: "Add README", "Update contents", "Introduce feature".
Prefix each commit message with the chapter it belongs to: `software-stack`, `data`, `compute`, `io`, `app-interact`.
How a good commit message should look like: <https://cbea.ms/git-commit/>

The use of `-s` / `--signoff` when creating a commit is optional, but strongly recommended.

### Setting Up GitHub Name and Email

To avoid common issues with authorship verification (such as []`checkpatch` errors](https://github.com/open-education-hub/operating-systems/actions/runs/6590761580/job/17908015178?pr=339#step:3:570)), it is important to make sure that your `git` configuration includes the correct name and email address, matching the ones associated with your GitHub account. You can configure this globally for all repositories or locally for a specific project.

To set your Git author information globally, run the following commands:

```bash
git config --global user.name "Your Name"
git config --global user.email "your-email@example.com"
```

If you prefer to set this information only for the current repository, omit the --global flag:

```bash
git config user.name "Your Name"
git config user.email "your-email@example.com"
```

These should match the name and email [address associated with your GitHub account ](https://github.com/settings/profile).
