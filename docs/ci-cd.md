# CI/CD Workflow: Building Windows DLLs for ConsolePortLK on Mac

This guide explains how to use GitHub Actions and the GitHub CLI to build and validate Windows DLLs for ConsolePortLK from any platform—including macOS—without needing a local Windows machine.

---

## 1. Prerequisites
- A GitHub repository for your project
- [GitHub CLI (`gh`)](https://cli.github.com/) installed on your Mac:
  ```sh
  brew install gh
  gh auth login  # Authenticate with your GitHub account
  ```

---

## 2. Workflow Overview
1. **Edit code locally** (on Mac or any OS)
2. **Commit and push** changes to GitHub
3. **GitHub Actions** automatically builds the DLL on a Windows VM
4. **Check build status and logs** using the GitHub CLI
5. **Download DLL artifacts** for testing on Windows
6. **Iterate as needed**

---

## 3. Using the GitHub CLI for CI/CD

### List recent workflow runs
```sh
gh run list
```

### View details and logs for a specific run
```sh
gh run view <run-id> --log
```

### Download build artifacts (DLLs, logs)
```sh
gh run download <run-id> --name controller_dll
```

- Replace `<run-id>` with the ID shown in `gh run list` output.
- Artifacts will be downloaded to your current directory.

---

## 4. Troubleshooting
- **Build fails:**
  - Use `gh run view <run-id> --log` to see compiler errors or warnings.
  - Update your code locally, commit, and push again.
- **No artifacts:**
  - Ensure the workflow YAML uploads the correct DLL path.
- **Authentication issues:**
  - Run `gh auth login` and follow prompts.

---

## 5. Best Practices
- Commit small, incremental changes for easier troubleshooting.
- Use pull requests to trigger builds and get feedback before merging to main.
- Keep your workflow YAML up to date as your project evolves.
- Document any special build requirements in your README or here.

---

## 6. References
- [GitHub Actions Documentation](https://docs.github.com/en/actions)
- [GitHub CLI Documentation](https://cli.github.com/manual/)
- Project workflow: `.github/workflows/windows-build.yml`

---

This workflow enables agentic and developer-driven Windows DLL development for ConsolePortLK from any platform.
