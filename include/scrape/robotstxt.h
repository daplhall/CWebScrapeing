#ifndef ROBOTTXT_C_WRAPPER_H
#define ROBOTTXT_C_WRAPPER_H
#ifdef __cplusplus
extern "C" {
#endif
int Scrape_allowed (char const *robot_txt, char const *user_agent,
		    char const *url);

#ifdef __cplusplus
}
#endif
#endif // ROBOTTXT_C_WRAPPER_H
