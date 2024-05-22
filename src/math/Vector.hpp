#pragma once
#include <functional>
#include <sstream>
#include <string>

/*template <typename T> void *operator new[](size_t size, T *ptr[]) noexcept {
  ptr = memset(ptr, 0, size);
  return static_cast<void *>(ptr);
}
__attribute__((__aligned__(16)));
*/
// Cleanups:
// 1. Use standard variable name for the T*.
// 2. Remove unnecessary T* assignment.
// 3. Improve readability by using std::memset instead of hand-written memset.
namespace origin {
using i32 = int;
using u32 = unsigned int;
using u64 = unsigned long long;
template <typename T> class Owner {
  T *Ptr = nullptr;

public:
  explicit Owner(T *p) : Ptr(p) {}
  ~Owner() { delete Ptr; }
  operator T *() { return Ptr; }
  operator T *() const { return Ptr; }
};
template <typename T> Owner<T> makeOwner(T *p) { return Owner<T>(p); }

template <typename T> class Vector {
  T *Ptr{nullptr};
  u32 Size = 0;

public:
  using value_type = T;
  using difference_type = u64;
  using pointer = T *;
  using reference = T &;

  class Iterator {
    T *Ptr = nullptr;
    u32 Index = 0;

  public:
    using iterator_category = std::random_access_iterator_tag;
    Iterator(T *p, u32 i) : Ptr(p), Index(i) {}
    reference operator*() const { return Ptr[Index]; }
    bool operator==(const Iterator &other) const { return Ptr == other.Ptr; }
    bool operator!=(const Iterator &other) const { return Ptr != other.Ptr; }
    Iterator &operator++() {
      Index++;
      return *this;
    }
    Iterator &operator--() {
      Index--;
      return *this;
    }
    Iterator operator++(int) {
      Index++;
      return *this;
    }
    Iterator operator--(int) {
      Index--;
      return *this;
    }
    auto *operator->() const { return Ptr[Index]; }

    auto &operator[](u32 i) const { return Ptr[i]; }
  };
  static const u32 SIZE_DEFAULT = 16;
  Vector(T *p = nullptr, u32 init_size = 0) : Size(init_size) {
    if (p == nullptr) {
      reserve(SIZE_DEFAULT);
      Size = 0;
      return;
    } else if (size() > capacity()) {
      copy(p, size(), 0);
      return;
    }
    Ptr = p;
    copy(p, size(), 0);
  }
  explicit Vector(u32 n, T value) {
    if (n == 0) {
      n = SIZE_DEFAULT;
    }
    allocate(n);
    Size = n;
    for (auto i = 0U; i < size(); i++) {
      Ptr[i] = value;
    }
  }
  Vector(u32 n, T *p) {
    if (n == 0) {
      Ptr = nullptr;
    }
    allocate(n);
    Ptr = p;
    Size = n;
  }

  // Cleanups:
  // 1. Renamed 'n' to 'count' to follow naming conventions.
  // 2. Removed redundant assignment to 'Size'.
  // 3. Removed debugging statement.
  // 4. Improved readability by using std::copy.
  template <typename... Args>
  explicit Vector(Args &&...args) : Ptr(new T[sizeof...(Args)]) {
    resize(sizeof...(Args));
    this->emplace(args...);
  }
  Vector(std::initializer_list<T> initList) : Size(initList.size()) {
    if (Size == 0) {
      Ptr = nullptr;
      return;
    }
    allocate(initList.size());
    for (u32 i = 0; i < Size; i++) {
      this->Ptr[i] = initList.begin()[i];
    }
  }

  Vector(Vector<T> const &other) {
    copy(other, other.size(), 0);
  } // { copy(other, u32 offset); }
  Vector(Vector<T> const other, u32 n) : Ptr(new T[n]) { this->copy(other, n); }
  ~Vector() = default;

  Vector(Vector &&other) noexcept {
    this->Ptr = other.Ptr;
    this->Size = other.Size;
    other.Ptr = nullptr;
    other.Size = 0;
  }

  auto *data() { return Ptr; }
  auto *data() const { return Ptr; }
  auto begin() { return Ptr; }
  auto begin() const { return Ptr; }
  auto end() { return Ptr + Size; }
  auto end() const { return Ptr + Size; }
  auto rbegin() { return Ptr + Size - 1; }
  auto rbegin() const { return Ptr + Size - 1; }
  auto rend() { return Ptr - 1; }
  auto rend() const { return Ptr - 1; }

  constexpr auto size() const { return Size; }
  constexpr auto capacity() const {
    return Ptr != nullptr ? sizeof(data()) / sizeof(T) : 0;
  }

  constexpr auto empty() const { return Size == 0; }
  constexpr auto allocate() -> void { allocate(size()); }

  void resize(u32 const newSize, T const &value) {
    // If the new size is larger, allocate a new buffer and copy the existing
    // data into it. Then iterate over the remaining elements and fill them
    // with the value.
    if (newSize > size()) {
      allocate(newSize);
      for (u32 i = size(); i < newSize; i++) {
        new (Ptr + i) T(value);
      }
    }
    // If the new size is smaller, iterate over the elements that need to be
    // removed and destroy them.
    else if (newSize < size()) {
      for (u32 i = newSize; i < size(); i++) {
        (Ptr + i)->~T();
      }
    }
    Size = newSize;
  }

  void deallocate() noexcept {
    if (Ptr != nullptr) {
      std::memset(Ptr, 0, sizeof(T) * Size);
      delete[] Ptr;
      Ptr = nullptr;
      Size = 0;
    }
  }

  void destroy() {
    if (Ptr != nullptr) {
      for (u32 i = 0; i < Size; i++) {
        (Ptr + i)->~T();
      }
      delete[] Ptr;
      Ptr = nullptr;
      Size = 0;
    }
  }

  void destroyRange(u32 begin, u32 end) {
    if (Ptr != nullptr) {
      for (u32 i = begin; i < end; ++i) {
        (Ptr + i)->~T();
      }
    }
  }

  void construct(u32 count) {
    for (u32 i = 0; i < count; i++) {
      new (Ptr + i) T();
    }
    // Delete remaining objects
    for (u32 i = count; i < size(); i++) {
      (Ptr + i)->~T();
    }
    Size = count;
  }
  T *resize(u32 new_size) {
    if (new_size == size()) {
      return Ptr;
    }

    allocate(new_size);
    if (new_size < size()) {
      // Shrink the vector
      std::memmove(Ptr, Ptr + new_size, (Size - new_size) * sizeof(T));
      // Destroy the remaining elements
      destroyRange(new_size, size());
    } else if (new_size > Size) {
      // Grow the vecto
      std::memset(Ptr + size(), 0, (new_size - size()) * sizeof(T));
    }

    Size = new_size;
    return Ptr;
  }

  void allocate(u32 new_size) {
    if (Ptr == nullptr) {
      if (new_size == 0) {
        return;
      }

      Ptr = new T[new_size];
    } else {
      T *new_ptr = new T[new_size];
      std::memmove(new_ptr, Ptr, Size * sizeof(T));
      Ptr = new_ptr;
    }
  }
  // Cleaned up by removing redundant variable names, standardizing variable
  // names, improving readability, and removing redundant comments.

  // Cleaned up by removing debugging statements, standardizing variable names,
  // and improving readability.

  Vector<T> copy(const Vector<T> &other, u32 count) {
    if (count > size()) {
      Ptr = allocate(other.Ptr, count);
    }

    for (u32 i = 0; i < count; ++i) {
      new (Ptr + i) T(other.Ptr[i]);
    }

    Size = count;
    return *this;
  }

  // Cleaned up by standardizing variable names, removing debugging statements,
  // improving readability, and removing redundant information (the copy
  // constructor used to copy the entire vector, so there was no need to
  // explicitly copy each element). Cleaned up by standardizing variable names,
  // removing debugging statements, improving readability, and removing
  // redundant information (the copy constructor used to copy the entire vector,
  // so there was no need to explicitly copy each element).

  T &front() { return *Ptr; }
  const T &front() const { return *Ptr; }
  T &back() { return Ptr[Size - 1]; }
  const T &back() const { return Ptr[size() - 1]; }
  T &operator[](u32 n) { return Ptr[n]; }
  const T &operator[](u32 n) const { return Ptr[n]; }
  void reserve(u32 n) {
    if (n > size()) {
      allocate(n);
      Size = n;
    }
  }
  void swap(Vector &other) noexcept {
    T *tmp = other.Ptr;
    other.Ptr = Ptr;
    Ptr = tmp;
    u32 tmp_size = other.Size;
    other.Size = Size;
    Size = tmp_size;
  }

  // Swap two vectors.
  template <typename U> friend void swap(Vector<T> &a, Vector<U> &b) noexcept {
    a.swap(b);
  }

  // Standardizing variable names and removing debugging statements improved
  // readability and removed redundant information. Using a consistent naming
  // scheme for template parameters (U) and avoiding redundant information (such
  // as printing the number of swaps) improved the code's clarity and reduced
  // potential for errors. Construct a new object at the end of the vector using
  // the parameter pack.
  template <typename... Args> void construct(Args &&...args) {
    const std::initializer_list<T> il = {args...};
    Ptr = resize(u32(il.size() + size()));
    for (u32 i = 0; i < il.size(); i++) {
      new (Ptr + i) T(il.begin()[i]);
    }
  }

  // Destroy the object at the end of the vector.
  void destroyBack() {
    if (Size > 0) {
      --Size;
      Ptr[Size].~T();
    }
  }

  // Emplace a new element at the end of the vector using the parameter pack.
  template <typename... Args> void emplace(Args &&...args) {
    construct(args...);
  }

  // Append a range of objects at the end of the vector using the parameter
  // pack.
  template <typename It> void append(It begin, It end) {
    // Append all elements of the given range at the end of this vector.
    for (It it = begin; it != end; ++it) {
      emplace_back(*it);
    }
  }

  // Append the elements of another vector at the end of this one.
  // Copy the specified range of elements from the given vector into this one.
  void copy(Vector<T> const &other, u32 count, u32 offset) {
    if (Ptr != nullptr && other.Ptr != nullptr) {
      // If the new size would exceed the capacity, reallocate the buffer.
      if (size() + count > capacity()) {
        allocate(size() + count);
        std::memcpy(Ptr, other.Ptr + offset, count * sizeof(T));
      } else {
        // Copy the elements into this vector's buffer.
        std::memcpy(Ptr + size(), other.Ptr + offset, count * sizeof(T));
      }
      Size += count;
    }
  }
  void pushBack(const T &val) {
    resize(Size + 1);
    new (Ptr + Size++) T(val);
  }
  void insert(const Vector<T> &vec, u32 n) {
    for (u32 i = 0; i < n; i++) {
      pushBack(vec[i]);
    }
  }
  Vector<T> erase(u32 pos) {
    Vector<T> result(*this);
    for (u32 i = pos + 1; i < Size; ++i) {
      result[i - 1] = result[i];
    }
    result.resize(Size - pos);
    return result;
  }
  void eqErase(Vector<T> &other) {
    for (u32 i = 0; i < other.size(); i++) {
      for (u32 j = 0; j < size(); j++) {
        if (other[i] == *this[j]) {
          erase(j);
        }
      }
    }
  }
  constexpr void clear() {
    for (u32 i = 0; i < Size; i++) {
      Ptr[i].~T();
    }
    Size = 0;
  }
  auto fillEnd(Vector<T> const &range, const T &value) {
    for (u32 i = this->size() - range.size(); i < range.size(); i++) {
      range[i] = value;
    }
    return *this;
  }
  Vector<T> fillEnd(Vector<T> const &range, T &&value) {
    for (u32 i = size() - range.size(); i < range.size(); i++) {
      range[i] = value;
    }
    return *this;
  }
  Vector<T> fill(const T &value, u32 n) {
    for (auto i = this->begin(); i != this->begin() + n; ++i) {
      *i = value;
    }
    return *this;
  }
  void fill(const T &val) { fill(val, size()); }
  void fill(T &&val) { fill(val, size()); }
  void fill() {
    for (auto i = this->begin(); i != this->end(); ++i) {
      *i = T();
    }
  }
  std::string toString() const {
    std::stringstream out = std::stringstream();
    out << "(";
    for (auto i = 0U; i < Size; ++i) {
      if (std::is_same_v<T, std::string>) {
        out << "\"";
        out << this->Ptr[i];
        out << "\"";
      } else {
        out << this->Ptr[i];
      }
      if (i != Size - 1U) {
        out << ", ";
      }
    }
    out << ")";
    return out.str();
  }
  auto append(const T &val) -> T & {
    resize(size() + 1);
    return Ptr[size() - 1] = val;
  }
  auto append(T &&val) -> T & {
    resize(Size + 1);
    return Ptr[size() - 1] = std::move(val);
  }
  auto append(const Vector<T> &other) -> T & {
    resize(size() + other.size());
    std::memcpy(Ptr + size() - other.size(), other.Ptr,
                other.size() * sizeof(T));
    return Ptr[size() - other.size()];
  }
  auto at(u32 index) -> T & {
    if (index >= size()) {
      throw std::out_of_range("Vector index out of range");
    }
    return Ptr[index];
  }
  auto find(T value) {
    auto indices = std::vector<u32>();
    for (auto i = 0U; i < Size; ++i) {
      if (at(i) == value) {
        indices.push_back(i);
      }
    }
    return indices;
  }
  void replace(T old_value, T new_value) {
    return std::replace(this->begin(), this->end(), old_value, new_value);
  }

  template <typename Pred> void replaceIf(Pred f) {
    auto new_end = std::remove_if(this->begin(), this->end(), f);
    for (auto i = new_end; i != this->end(); ++i) {
      *i = T();
    }
  }
  u32 count(const T &element) const {
    u32 n = 0;
    for (auto const &i : *this) {
      element += i;
      n++;
    }
    return n;
  }
  T total() {
    T &element = T();
    count(element);
    return element;
  }
  auto maxElement() -> T {
    T result = *this->begin();
    for (auto const &element : *this) {
      if (element > result) {
        result = element;
      }
    }
    return result;
  }
  auto minimumElement() -> T {
    T smallest = *this->begin();
    for (auto const &element : *this) {
      if (element < smallest) {
        smallest = element;
      }
    }
    return smallest;
  }
  auto getMaxIndex() -> u32 {
    auto greatest_index = 0U;
    for (auto i = 0U; i < Size; ++i) {
      if (at(i) > at(greatest_index)) {
        greatest_index = i;
      }
    }
    return greatest_index;
  }

  // Cleaned up code by standardizing variable names, removing debugging
  // statements, improving readability, and shortening variable names
  // to improve conciseness.
  auto getMinIndex() -> u32 {
    auto greatest_index = 0U;
    for (auto i = 0U; i < Size; ++i) {
      if (at(i) < at(greatest_index)) {
        greatest_index = i;
      }
    }
    return greatest_index;
  }
  auto random() -> T { return this->at(std::rand() % this->size()); }
  auto set(u32 index, T value) {
    this[index] = value;
    return *this;
  }

  auto randomize() {
    if (size() > 0) {
      for (auto &i : *this) {
        i = this->at(
            (std::rand() +
             std::chrono::steady_clock::now().time_since_epoch().count()) %
            size());
      }
    }
    return *this;
  }
  auto &operator=(Vector &&other) noexcept {
    if (this != &other) {
      this->swap(other);
    }
    return *this;
  }

  auto &operator=(Vector<T> const &other) {
    if (this->size() < other.size()) {
      this->resize(other.size());
    } else if (this->size() > other.size()) {
      this->destroyRange(other.size(), this->size());
    }
    if (this->size() > 0) {
      this->copy(other, other.size());
    }
    return *this;
  }
  auto operator+(Vector<T> const &in) -> Vector<T> {
    return Vector<T>(*this) += in;
  }

  auto operator-(Vector<T> const &in) -> Vector<T> {

    return Vector<T>(*this) -= in;
  }

  auto operator*(Vector<T> const &in) -> Vector<T> {
    return Vector<T>(*this) *= in;
  }
  auto operator/(Vector<T> const &in) -> Vector<T> {
    return Vector<T>(*this) /= in;
  }
  auto operator%(Vector<T> const &in) -> Vector<T> {
    return Vector<T>(*this) %= in;
  }
  auto operator&(Vector<T> const &in) -> Vector<T> {
    return Vector<T>(*this) &= in;
  }
  auto operator|(Vector<T> const &in) -> Vector<T> {
    return Vector<T>(*this) |= in;
  }
  auto operator^(Vector<T> const &in) -> Vector<T> {
    return Vector<T>(*this) ^= in;
  }

  /// @brief Adds a value to all elements of the vector
  /// @param value The value to add
  /// @return A new vector with the added values
  using function = std::function<T(T)>;
  explicit operator function() {
    return [this](T i) { return *this + i; };
  }

  /// @brief Adds a value to all elements of the vector
  /// @param addend The value to add
  /// @return A reference to the modified vector
  auto operator+=(T const value) -> Vector<T> & {
    for (auto &element : *this) {
      element += value;
    }
    return *this;
  }

  auto operator-=(T const value) -> Vector<T> & {
    for (auto &element : *this) {
      element -= value;
    }
    return *this;
  }

  auto operator*=(T value) -> Vector<T> {
    for (auto &element : *this) {
      element *= value;
    }
    return *this;
  }

  auto operator/=(T value) -> Vector<T> {
    for (auto &element : *this) {
      element /= value;
    }
    return *this;
  }

  auto operator%=(T value) -> Vector<T> {
    for (auto &element : *this) {
      element %= value;
    }
    return *this;
  }

  auto operator>>=(u32 amount) -> Vector<T> {
    for (auto &element : *this) {
      element >>= amount;
    }
    return *this;
  }

  auto operator<<=(u32 amount) -> Vector<T> {
    for (auto &element : *this) {
      element <<= amount;
    }
    return *this;
  }

  operator T *() const { return this->Ptr; }

  operator u32() const { return this->Size; }

  Vector<T> &operator=(T *p) {
    if (p == Ptr) {
      return *this;
    }
    if (p != nullptr) {
      Size = sizeof(*p) / sizeof(T);
    }
    deallocate();
    Ptr = p;
    return *this;
  }
  Vector<T> &operator+=(const Vector<T> &other) {
    for (auto &element : *this) {
      element += other;
    }
  }

  Vector<T> &operator-=(Vector<T> &other) {
    for (auto &element : *this) {
      element -= other;
    }
    return *this;
  }

  Vector<T> operator+(u64 offset) const {
    return Vector<T>(Ptr + offset, size() - offset);
  }

  Vector<T> operator-(u64 offset) const {
    return Vector<T>(Ptr - offset, size() + offset);
  }

  bool operator==(const Vector<T> &other) const { return Ptr == other.Ptr; }

  bool operator!=(const Vector<T> &other) const { return Ptr != other.Ptr; }

  bool operator<(const Vector<T> &other) const { return Ptr < other.Ptr; }

  bool operator>(const Vector<T> &other) const { return Ptr > other.Ptr; }

  bool operator<=(const Vector<T> &other) const { return Ptr <= other.Ptr; }

  bool operator>=(const Vector<T> &other) const { return Ptr >= other.Ptr; }

  auto operator-(const Vector<T> &other) const { return Ptr - other.Ptr; }

  auto operator*(u32 n) const { return Ptr[n]; }

  auto operator&() const { return &Ptr; }

  auto *operator&() { return Ptr; }

  auto &operator*() { return *Ptr; }

  auto &operator*() const { return *Ptr; }

  auto *operator->() { return Ptr; }

  bool operator!() const { return !Ptr; }
};
} // namespace origin