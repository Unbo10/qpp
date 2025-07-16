
# Commit guide

When making a commit the basic structure you are going to follow is:

```sh
<type>(scope): <short summary>

[optional body]
```

The prefered language of the commits is English, but it's fine if you add some Spanish as long as you maintain the structure. Either way, make sure to use the present tense.

## 🔹 Common Commit Types

| Type       | Description                                              |
|------------|----------------------------------------------------------|
| `feat`     | A new feature                                            |
| `fix`      | A bug fix                                                |
| `chore`    | Maintenance (e.g. build, config, dependencies)           |
| `docs`     | Documentation only changes                              |
| `style`    | Formatting, missing semi-colons, etc; no code change     |
| `refactor` | Code change that neither fixes a bug nor adds a feature |
| `perf`     | Performance improvement                                  |
| `test`     | Adding or updating tests                                 |
| `ci`       | Continuous integration-related changes                   |

---

## 🔹 Scope

- Optional but recommended.
- Helps identify the area of the codebase being changed.
- Some of the ones we may use are the following:

| Scope        | Description                                |
|--------------|--------------------------------------------|
| `numbers`    | Changes to fundamental numeric types       |
| `integer`    | Changes to the Integer class specifically  |
| `rational`   | Changes to the Rational class              |
| `utils`      | Changes to utility classes like List       |
| `operations` | Math operation implementations             |
| `tests`      | Test-related changes                       |
| `docs`       | Documentation updates                      |
| `build`      | Build system changes                       |

## 🔹 Summary

- Start with a **lowercase verb** (imperative mood).
- Keep it **under 50 characters**.
- Be specific and concise.

❌ `fixed bug`  
✅ `fix(auth): redirect after logout`

---

## 🔹 Body (optional but encouraged for non-trivial changes)

- Use when the **"what"** in the summary doesn’t explain the **"why"** or **"how"**.
- Explain **reasoning**, **context**, or **impact**.

---


## 🔹Examples

>Tip: To add a new line or line break to a commit, press `Shift + Enter`.

Feature addition:

```sh
git commit -m "feat(rational): implement input operator for Rational" -m "- Add stream extraction operator (>>) to parse fractions
- Handle different input formats (1/2, -3/4)
- Add proper error handling for invalid inputs like '/' or '3/'
- Ensure sign handling is consistent with mathematical conventions"
```

Bug fix:

```sh
git commit -m "fix(integer): make unary minus operator const" -m "The operator-() method was missing the const qualifier, causing errors when used with const Integer objects.
This prevented operations like negating integers in the binaryEuclidean method.

Fixed by adding const qualifiers to both base class declaration and implementation."
```

Refactoring (changes to the repo's organization):
```sh
git commit -m "refactor(numbers): improve operator overloading consistency" -m "- Make compound operators (+=, -=) return references
- Define operators in terms of basic ones to reduce code duplication
- Fix setSign method to properly modify the object instead of the parameter"
```

Performance improvement:
```sh
git commit -m "perf(integer): optimize karatsuba multiplication algorithm" -m "Reduced recursion threshold from 30 to 15 digits, resulting in 25% faster multiplication for large integers.

Benchmark results:
- Before: 450ms for 10000-digit multiplication
- After: 335ms for 10000-digit multiplication"
```