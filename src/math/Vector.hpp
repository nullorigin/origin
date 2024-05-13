#pragma once
#include <functional>
#include <map>
#include <numeric>
#include <regex>
#include <string>
#include <vector>
namespace origin
{
    template<typename T>
    class Vector : public std::vector<T>
    {
    public:
        using vector = Vector<T>;
        using iterator = typename std::vector<T>::iterator;
        using value_type = typename std::vector<T>::value_type;
        using pointer = typename std::vector<T>::pointer;
        using reference = typename std::vector<T>::reference;
        using allocator_type = typename std::vector<T>::allocator_type;
        using size_type = typename std::vector<T>::size_type;
        using difference_type = typename std::vector<T>::difference_type;
        using const_reference = typename std::vector<T>::const_reference;
        using const_pointer = typename std::vector<T>::const_pointer;
        using const_iterator = typename std::vector<T>::const_iterator;
        using reverse_iterator = typename std::vector<T>::reverse_iterator;
        using const_reverse_iterator =
            typename std::vector<T>::const_reverse_iterator;
        auto toString()
        {
            std::string out = "Vector(";
            for (size_type i = 0; i < size(); ++i)
            {
                out = out.append(std::to_string(this->at(i)));
                if (i != size() - 1)
                {
                    out = out.append(", ");
                }
            }
            out = out.append(")");
            return out;
        }
        Vector() = default;
        Vector(const Vector& rhs) :
            std::vector<T>(rhs) {}
        Vector& operator=(const Vector& rhs) noexcept
        {
            copy(rhs);
            return *this;
        }
        Vector(Vector&& rhs) noexcept :
            std::vector<T>(move(rhs))
        {
            *this = move(rhs);
        }
        Vector& operator=(Vector&& rhs) noexcept
        {
            std::vector<T>::operator=(move(rhs));
            return *this;
        };
        ~Vector() = default;
        template<typename... Args>
        explicit Vector(Args... args) :
            std::vector<T>(args...)
        {
            *this = std::vector<T>(args...);
        }
        Vector(std::initializer_list<T> list) :
            std::vector<T>(list) {}
        explicit Vector(size_type size) :
            std::vector<T>(size)
        {
            if (size > 0)
            {
                reserve(size);
                fill(this->begin(), this->end(), 0);
            }
        }
        explicit Vector(size_type size, const_reference value) :
            std::vector<T>(size, value)
        {
            if (size > 0)
            {
                reserve(size);
                fill(this->begin(), this->end(), value);
            }
        }
        Vector(size_type size, value_type value) :
            std::vector<T>(size, value) {}
        Vector(size_type size, pointer values) :
            std::vector<T>(size, *values) {}
        Vector(size_type size, value_type value, allocator_type alloc) :
            std::vector<T>(size, value, alloc) {}
        Vector(size_type size, pointer values, allocator_type alloc) :
            std::vector<T>(size, *values, alloc) {}
        Vector(iterator it, size_type size) :
            std::vector<T>(size, *it)
        {
            this->assign(it, it + size);
        }

        typename std::vector<T>::iterator begin() noexcept
        {
            return std::vector<T>::begin();
        }
        typename std::vector<T>::iterator end() noexcept
        {
            return std::vector<T>::end();
        }
        template<typename U>
        constexpr auto cast(U c) -> U
        {
            return (c);
        }
        void pushBack(value_type value) { std::vector<T>::push_back(value); }

        void popBack() { std::vector<T>::pop_back(); }
        auto data() { return std::vector<T>::data(); }
        void clear() { std::vector<T>::clear(); }
        void erase(const_iterator pos) { std::vector<T>::erase(pos); }
        void erase(const_iterator first, const_iterator last)
        {
            std::vector<T>::erase(first, last);
        }
        bool empty() const { return std::vector<T>::empty(); }
        size_type size() const { return std::vector<T>::size(); }
        size_type maxSize() const { return std::vector<T>::max_size(); }
        size_type capacity() const { return std::vector<T>::capacity(); }
        void resize(size_type size) { std::vector<T>::resize(size); }

        void assign(size_type size, value_type value)
        {
            std::vector<T>::assign(size, value);
        }

        void assign(size_type size, pointer values)
        {
            for (size_type i = 0; i < size; ++i)
            {
                this->pushBack(values[i]);
            }
        }

        void assign(size_type size, pointer values, size_type offset)
        {
            for (size_type i = 0; i < size; ++i)
            {
                this->pushBack(values[i + offset]);
            }
        }
        const_iterator begin() const noexcept { return std::vector<T>::begin(); }
        const_iterator end() const noexcept { return std::vector<T>::end(); }
        const_iterator cbegin() const noexcept { return std::vector<T>::cbegin(); }
        const_iterator cend() const noexcept { return std::vector<T>::cend(); }
        const_reverse_iterator crbegin() const noexcept
        {
            return std::vector<T>::crbegin();
        }
        const_reverse_iterator crend() const noexcept
        {
            return std::vector<T>::crend();
        }
        reverse_iterator rbegin() { return std::vector<T>::rbegin(); }
        reverse_iterator rend() { return std::vector<T>::rend(); }
        typename std::vector<T>::iterator append(Vector in)
        {
            this->reserve(this->size() + in.size());
            for (auto it = in.begin(); it != in.end(); ++it)
            {
                this->pushBack(*it);
            }
            return begin();
        }
        typename std::vector<T>::iterator prepend(Vector in)
        {
            this->reserve(this->size() + in.size());
            for (auto it = in.rbegin(); it != in.rend(); ++it)
            {
                this->insert(begin(), *it);
            }
            return this->begin();
        }
        void resizeAndOverwrite(size_type n, value_type value)
        {
            this->resize(n);
            this->fill(this->begin(), this->end(), value);
        }
        auto at(size_type index) { return std::vector<T>::at(index); }
        auto copy(Vector in)
        {
            std::copy(in.begin(), in.end(), this->begin());
        }
        auto move(Vector in)
        {
            return std::move(in.begin(), in.end(), this->begin());
        }
        void destroy() { this->clear(); }
        void shift(size_type count)
        {
            std::vector<T>::erase(this->begin(), this->begin() + count);
        }
        void popFront() { std::vector<T>::erase(this->begin()); }
        void swap(Vector& in) { std::vector<T>::swap(in); }
        auto emplaceBack(value_type&& args...)
        {
            return std::vector<T>::emplaceBack(args);
        }
        typename std::vector<T>::iterator emplace(const_iterator pos,
                                                  value_type&& args...)
        {
            return std::vector<T>::emplace(pos, args);
        }
        typename std::vector<T>::iterator insert(const_iterator pos,
                                                 value_type value)
        {
            return std::vector<T>::insert(pos, value);
        }
        void resizeCheck(size_type size)
        {
            if (size != std::vector<T>::size() && size != this->size())
            {
                this->reserve(size);
                std::vector<T>::resize(size);
            };
        }
        void reserve(size_type size) { std::vector<T>::reserve(size); }
        void shrinkToFit() { std::vector<T>::shrink_to_fit(); }
        void sort() { std::sort(this->begin(), this->end()); }
        void reverse() { std::reverse(this->begin(), this->end()); }
        void fill(value_type value) { std::fill(this->begin(), this->end(), value); }
        void fill(size_type size, value_type value)
        {
            std::fill(this->begin(), this->begin() + size, value);
        }
        void fill(size_type x, size_type y, value_type value)
        {
            std::fill(this->begin() + x, this->begin() + y, value);
        }
        auto back() { return std::vector<T>::back(); }
        auto front() { return std::vector<T>::front(); }
        auto regexSearch(const std::basic_regex<value_type>& rx) { return std::regex_search(rx, this->begin(), this->end()); }
        auto regexReplace(const std::basic_regex<value_type>& rx, const value_type& rep) { return std::regex_replace(this->begin(), this->end(), rx, rep); }
        auto transform(Vector& in,
                       std::function<void(value_type&, value_type&)> f)
        {
            return std::transform(this->begin(), this->end(), in.begin(), in.end(), f);
        }
        auto find(value_type value) -> iterator
        {
            return std::find(this->begin(), this->end(), value);
        }
        void replace(value_type old_value, value_type new_value)
        {
            return std::replace(this->begin(), this->end(), old_value, new_value);
        }
        void replace(size_type x, size_type y, value_type value)
        {
            return std::replace(this->begin() + x, this->begin() + y, value);
        }
        void replaceIf(const_iterator first, const_iterator last, std::function<bool(value_type)> f)
        {
            return std::replace_if(this->begin(), this->end(), first, last, f);
        }
        size_type count(const value_type& value)
        {
            return std::count(this->begin(), this->end(), value);
        }
        size_type sum(const value_type& value)
        {
            return std::accumulate(this->begin(), this->end(), value);
        }
        size_type sum() { return std::accumulate(this->begin(), this->end(), 0); }
        auto max() -> value_type
        {
            return *std::max_element(this->begin(), this->end());
        }
        auto min() -> value_type
        {
            return *std::min_element(this->begin(), this->end());
        }
        auto maxIndex() -> size_type
        {
            return std::distance(this->begin(),
                                 std::max_element(this->begin(), this->end()));
        }
        auto minIndex() -> size_type
        {
            return std::distance(this->begin(),
                                 std::min_element(this->begin(), this->end()));
        }
        auto random() -> value_type { return this->at(std::rand() % this->Size()); }
        auto set(size_type index, value_type value)
        {
            this[index] = value;
            return *this;
        }
        auto set(size_type offset, pointer values) -> Vector
        {
            std::copy(values, values + this->size(), this->begin() + offset);
            return *this;
        }
        auto randomize() -> Vector
        {
            for (auto& i : *this)
            {
                i = this->at(std::rand() % this->size());
            }
            return *this;
        }
        auto operator+(Vector& in) -> Vector
        {
            Vector out(*this);
            return out += in;
        }

        auto operator-(Vector& in) -> Vector
        {
            Vector out(*this);
            return out -= in;
        }

        auto operator*(Vector& in) -> Vector
        {
            Vector out(*this);
            return out *= in;
        }

        auto operator/(Vector& in) -> Vector
        {
            Vector out(*this);
            return out /= in;
        }
        auto operator%(Vector& in) -> Vector
        {
            Vector out(*this);
            return out %= in;
        }
        auto operator&(Vector& in) -> Vector
        {
            Vector out(*this);
            return out &= in;
        }
        auto operator|(Vector& in) -> Vector
        {
            Vector out(*this);
            return out |= in;
        }
        auto operator^(Vector& in) -> Vector
        {
            Vector out(*this);
            return out ^= in;
        }
        auto operator=(value_type value) -> Vector&
        {
            std::fill(this->begin(), this->end(), value);
            return *this;
        }
        auto operator=(Vector in) noexcept -> Vector&
        {
            std::move(this->begin(), this->end(), in.begin());
            swap(in);
            return *this;
        }
        auto operator+=(Vector& in) -> Vector&
        {
            std::transform(this->begin(), this->end(), in.begin(), this->begin(), std::plus<value_type>());
            return *this;
        }
        auto operator-=(Vector& in) -> Vector&
        {
            std::transform(this->begin(), this->end(), in.begin(), this->begin(), std::minus<value_type>());
            return *this;
        }
        auto operator*=(Vector& in) -> Vector&
        {
            std::transform(this->begin(), this->end(), in.begin(), this->begin(), std::multiplies<value_type>());
            return *this;
        }
        auto operator/=(Vector& in) -> Vector&
        {
            std::transform(this->begin(), this->end(), in.begin(), this->begin(), std::divides<value_type>());
            return *this;
        }
        template<typename U>
        auto operator%=(Vector<U>& in) -> Vector&
        {
            Vector<T>* out = *this;
            std::transform(out->begin(), out->end(), in.begin(), out->begin(), std::modulus<U>());
            return *this = *out;
        }
        template<typename U>
        auto operator&=(Vector<U>& in) -> Vector&
        {
            std::transform(this->begin(), this->end(), in.begin(), this->begin(), std::bit_and<U>());
            return *this;
        }
        template<typename U>
        auto operator|=(Vector<U>& in) -> Vector&
        {
            std::transform(this->begin(), this->end(), in.begin(), this->begin(), std::bit_or<U>());
            return *this;
        }
        template<typename U>
        auto operator^=(Vector<U>& in) -> Vector&
        {
            std::transform(this->begin(), this->end(), in.begin(), this->begin(), std::bit_xor<U>());
            return *this;
        }

        auto operator-() -> Vector
        {
            Vector out(*this);
            std::transform(out->begin(), out.end(), out.begin(), std::negate<value_type>());
            return out;
        }
        auto operator!() -> Vector
        {
            Vector out(*this);
            std::transform(out->begin(), out.end(), out.begin(), std::logical_not<value_type>());
            return out;
        }
        auto operator++() -> Vector&
        {
            std::transform(this->begin(), this->end(), this->begin(), std::plus<value_type>());
            return *this;
        }
        auto operator--() -> Vector&
        {
            std::transform(this->begin(), this->end(), this->begin(), std::minus<value_type>());
            return *this;
        }
        auto operator++(int) -> Vector
        {
            std::transform(this->begin(), this->end(), this->begin(), std::plus<value_type>());
            return *this;
        }
        auto operator--(int) -> Vector
        {
            std::transform(this->begin(), this->end(), this->begin(), std::minus<value_type>());
            return *this;
        }
        bool operator==(Vector& in)
        {
            return std::equal(this->begin(), this->end(), in.begin());
        }
        bool operator!=(Vector& in)
        {
            return !std::equal(this->begin(), this->end(), in.begin());
        }
        bool operator<(Vector& in)
        {
            return std::lexicographical_compare(this->begin(), this->end(), in.begin(), in.end());
        }
        bool operator>(Vector& in)
        {
            return std::lexicographical_compare(this->begin(), this->end(), in.begin(), in.end(), std::greater<value_type>());
        }
        bool operator<=(Vector& in)
        {
            return !std::lexicographical_compare(this->begin(), this->end(), in.begin(), in.end(), std::greater<value_type>());
        }
        bool operator>=(Vector& in)
        {
            return !std::lexicographical_compare(this->begin(), this->end(), in.begin(), in.end());
        }
        bool operator&&(Vector& in)
        {
            return std::inner_product(this->begin(), this->end(), in.begin(), (cast<value_type>(0)));
        }
        bool operator||(Vector& in)
        {
            return std::inner_product(this->begin(), this->end(), in.begin(), (cast<value_type>(0)));
        }
        auto operator+(value_type value) -> Vector
        {
            Vector out(*this);
            for (auto& i : out)
            {
                i += value;
            }
            return out;
        }
        using function = std::function<value_type(value_type)>;
        operator function() const
        {
            return [&](function f) {
                for (auto& i : *this)
                {
                    i = f(i);
                }
                return *this;
            };
        }
        auto operator-(value_type value) -> Vector
        {
            Vector out(*this);
            for (auto& i : out)
            {
                i -= value;
            }
            return out;
        }

        auto operator*(value_type value) -> Vector
        {
            Vector out(*this);
            for (auto& i : out)
            {
                i *= value;
            }
            return out;
        }

        auto operator/(value_type value) -> Vector
        {
            Vector out(*this);
            for (auto& i : out)
            {
                i /= value;
            }
            return out;
        }

        auto operator%(value_type value) -> Vector
        {
            Vector out(*this);
            for (auto& i : out)
            {
                i %= value;
            }
            return out;
        }

        auto operator>>(value_type value) -> Vector
        {
            Vector out(*this);
            for (auto& i : out)
            {
                i >>= value;
            }
            return out;
        }

        auto operator<<(value_type value) -> Vector
        {
            Vector out(*this);
            for (auto& i : out)
            {
                i <<= value;
            }
            return out;
        }
        auto operator+=(value_type value) -> Vector
        {
            for (auto& i : *this)
            {
                i += value;
            }
            return *this;
        }

        auto operator-=(value_type value) -> Vector
        {
            for (auto& i : *this)
            {
                i -= value;
            }
            return *this;
        }

        auto operator*=(value_type value) -> Vector
        {
            for (auto& i : *this)
            {
                i *= value;
            }
            return *this;
        }

        auto operator/=(value_type value) -> Vector
        {
            for (auto& i : *this)
            {
                i /= value;
            }
            return *this;
        }
        auto operator%=(value_type value) -> Vector
        {
            for (auto& i : *this)
            {
                i %= value;
            }
            return *this;
        }

        auto operator>>=(value_type value) -> Vector
        {
            for (auto& i : *this)
            {
                i >>= value;
            }
            return *this;
        }

        auto operator<<=(value_type value) -> Vector
        {
            for (auto& i : *this)
            {
                i <<= value;
            }
            return *this;
        }
        Vector& operator=(std::initializer_list<T> list)
        {
            assign(*list.begin(), list.size());
            return *this;
        }
        auto operator[](size_type index) -> T& { return *data() + index; }

        explicit operator pointer() const { return data(); }

        explicit operator size_type() const { return size(); }

        explicit operator size_type() { return size(); }
    };
} // namespace origin