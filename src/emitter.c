#include "../include/emitter.h"

Emitter* add_emitter(int32_t x, int32_t y, uint32_t maxParticles, uint32_t idFlags) {
  Emitter* em;
  em = malloc(sizeof(Emitter));
  memset(em, 0, sizeof(Emitter));

  em->x = x;
  em->y = y;
  em->maxParticles = maxParticles;
  em->idFlags = idFlags;
  em->particleTail = &em->particleHead;

  return em;
}

void emitter_update(Emitter* em) {
  Entity* p;
  Entity* prev;
  prev = &em->particleHead;

  for (p = em->particleHead.next; p != NULL; p = p->next) {    
    particle_update(p);

    if (p->flags & DEATH_MASK) {
      if (p == em->particleTail) {
        em->particleTail = prev;
      }

      prev->next = p->next;
      particle_die(p);
      p = prev;
    }

    prev = p;
  }
}

void emitter_draw(Emitter* em) {
  Entity* p;

  for (p = em->particleHead.next; p != NULL; p = p->next) {
    particle_draw(p);
  }
}

void spawn_blood_particles(Emitter* em, int32_t x, int32_t y, uint32_t n, uint32_t idFlags) {
  for (int i = 0; i < n; i++) {
    bool scatterParticle = randomInt(0, 1);
    float dx = randomFloat(-20.0f, 20.0f);
    float dy = randomFloat(-15.0f, 10.0f);
    float decX;
    float decY;
    float deltaAlpha;

    if (!scatterParticle) {
      decX = randomFloat(0.50f, 0.70f);
      decY = randomFloat(0.50f, 0.70f);
    } else {
      decX = randomFloat(0.70f, 0.95f);
      decY = randomFloat(0.70f, 0.95f);
      deltaAlpha = randomFloat(1.0f, 3.0f);
    }

    uint16_t w = randomInt(1, 10);
    uint16_t h = w;
    uint8_t r = randomInt(20, 0xff);
    uint8_t g = 0;
    uint8_t b = 0;
    uint8_t a = 0xff;
    uint16_t angle = 0;

    Entity* en;
    en = add_particle(x, y, dx, dy, decX, decY, w, h, angle, r, g, b, a, deltaAlpha, idFlags);

    if (em != NULL) {
      em->particleTail->next = en;
      em->particleTail = en;
    } else {
      exit(EXIT_FAILURE);
    }
  }
}