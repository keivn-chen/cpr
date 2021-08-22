#ifndef CPR_REDIRECT_H
#define CPR_REDIRECT_H

#include <cstdint>

namespace cpr {
enum class PostRedirectFlags : uint8_t {
    /**
     * Respect RFC 7231 (section 6.4.2 to 6.4.4).
     * Same as CURL_REDIR_POST_301 (https://curl.se/libcurl/c/CURLOPT_POSTREDIR.html).
     **/
    POST_301 = 0x1 << 0,
    /**
     * Maintain the request method after a 302 redirect.
     * Same as CURL_REDIR_POST_302 (https://curl.se/libcurl/c/CURLOPT_POSTREDIR.html).
     **/
    POST_302 = 0x1 << 1,
    /**
     * Maintain the request method after a 303 redirect.
     * Same as CURL_REDIR_POST_303 (https://curl.se/libcurl/c/CURLOPT_POSTREDIR.html).
     **/
    POST_303 = 0x1 << 2,
    /**
     * Default value.
     * Convenience option to enable all flags.
     * Same as CURL_REDIR_POST_ALL (https://curl.se/libcurl/c/CURLOPT_POSTREDIR.html).
     **/
    POST_ALL = POST_301 | POST_302 | POST_303,
    /**
     * * Convenience option to disable all flags.
     **/
    NONE = 0x0
};

PostRedirectFlags operator|(PostRedirectFlags lhs, PostRedirectFlags rhs);
PostRedirectFlags operator&(PostRedirectFlags lhs, PostRedirectFlags rhs);
PostRedirectFlags operator^(PostRedirectFlags lhs, PostRedirectFlags rhs);
PostRedirectFlags operator~(PostRedirectFlags flag);
PostRedirectFlags& operator|=(PostRedirectFlags& lhs, PostRedirectFlags rhs);
PostRedirectFlags& operator&=(PostRedirectFlags& lhs, PostRedirectFlags rhs);
PostRedirectFlags& operator^=(PostRedirectFlags& lhs, PostRedirectFlags rhs);
bool any(PostRedirectFlags flag);

class Redirect {
  public:
    /**
     * The maximum number of redirects to follow.
     * 0: Refuse any redirects.
     * -1: Infinite number of redirects.
     * Default: 50
     * https://curl.se/libcurl/c/CURLOPT_MAXREDIRS.html
     **/
    // NOLINTNEXTLINE (cppcoreguidelines-avoid-magic-numbers, google-runtime-int)
    long max{50L};
    /**
     * Follow 3xx redirects.
     * Default: true
     * https://curl.se/libcurl/c/CURLOPT_FOLLOWLOCATION.html
     **/
    bool follow{true};
    /**
     * Flags to control how to act after a redirect for a post request.
     * Default: POST_ALL
     **/
    PostRedirectFlags post_flags{PostRedirectFlags::POST_ALL};

    Redirect() = default;
    // NOLINTNEXTLINE (google-runtime-int)
    Redirect(long max, bool follow, PostRedirectFlags post_flags) : max(max), follow(follow), post_flags(post_flags){};
    // NOLINTNEXTLINE (google-runtime-int)
    explicit Redirect(long max) : max(max){};
    explicit Redirect(bool follow) : follow(follow){};
    explicit Redirect(PostRedirectFlags post_flags) : post_flags(post_flags){};
};
} // namespace cpr

#endif